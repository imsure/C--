/**
 * Routines for generating 3-address-code from syntax tree.
 * ********************************************************
 *
 * Author: Shuo Yang
 * Email: imsure95@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "protos.h"
#include "three-address-code.h"
#include "syntax-tree.h"

int label_counter = 0; // counter for the labels.
int tmp_counter = 0; // counter for the temp variables.

instr *newinstr( optype op, address *operand1,
		 address *operand2, address *dest )
{
  instr *quad = (instr *) zalloc( sizeof(instr) );
  quad->op = op;
  quad->dest = dest;
  quad->operand1 = operand1;
  quad->operand2 = operand2;
  quad->next = NULL;

  return quad;
}

void print_code( tnode *t )
{
  instr *inst;
  symtabnode *stptr;
  instr *end = t->code->end;

  for (inst = t->code->start; inst != NULL; inst = inst->next) {
    printf( "op: %d, ", inst->op );
    if ( inst->operand1 != NULL ) {
      switch (inst->operand1->atype) {
      case AT_Intcon:
	printf( "operand1: %d, ", inst->operand1->val.iconst );
	break;
      case AT_StRef:
	printf( "operand1: %s, ", inst->operand1->val.stptr->name );
	break;
      }
    }

    if ( inst->operand2 != NULL ) {
      switch (inst->operand2->atype) {
      case AT_Intcon:
	printf( "operand2: %d, ", inst->operand2->val.iconst );
	break;
      case AT_StRef:
	printf( "operand2: %s, ", inst->operand2->val.stptr->name );
	break;
      }
    }

    if ( inst->dest != NULL ) {
      switch (inst->dest->atype) {
      case AT_Intcon:
	printf( "dest: %d", inst->dest->val.iconst );
	break;
      case AT_StRef:
	printf( "dest: %s", inst->dest->val.stptr->name );
	break;
      }
    }
    putchar( '\n' );
  }
}

three_addr_code *code_gen( tnode *t )
{
  symtabnode *stptr;
  tnode *tntmp;
  optype op;
  address *dest, *operand1, *operand2;
  three_addr_code *tmpcode, *tmpcode2;

  if ( t == NULL ) {
    fprintf( stderr, "null tree node\n" );
    return NULL;
  }

  switch ( t->ntype ) {
  case Error:
    fprintf( stderr, "Error!\n" );
    break;
  case Intcon:
    printf( "Generating code for Intcon...\n" );
    t->place = newtmp();
    op = TAC_Assg;
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_Intcon;
    operand1->val.iconst = stIntcon( t );
    operand2 = (address *) NULL;
    dest = (address *) zalloc( sizeof(address) );
    dest->atype = AT_StRef;
    dest->val.stptr = t->place;
    t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
    t->code->start = newinstr( op, operand1, operand2, dest );
    t->code->end = t->code->start;
    //print_code( t );
    break;
  case Var:
    stptr = stVar( t );
    t->place = stptr;
    t->code = NULL; // no instruction needed.
    break;
  case Plus:
    printf( "Generating code for plus...\n" );
    tmpcode = code_gen( stBinop_Op1(t) );
    tmpcode2 = code_gen( stBinop_Op2(t) );
    t->place = newtmp();
    op = TAC_Plus;
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_StRef;
    operand1->val.stptr = stBinop_Op1(t)->place;
    operand2 = (address *) zalloc( sizeof(address) );
    operand2->atype = AT_StRef;
    operand2->val.stptr = stBinop_Op2(t)->place;
    dest = (address *) zalloc( sizeof(address) );
    dest->atype = AT_StRef;
    dest->val.stptr = t->place;
    t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
    if ( tmpcode == NULL && tmpcode2 == NULL ) {
      t->code->start = newinstr( op, operand1, operand2, dest );
      t->code->end = t->code->start;
    } else if ( tmpcode == NULL && tmpcode2 != NULL ) {
      t->code = tmpcode2;
      t->code->end->next = newinstr( op, operand1, operand2, dest );
      t->code->end = t->code->end->next;
    } else if ( tmpcode != NULL && tmpcode2 == NULL ) {
      t->code = tmpcode;
      t->code->end->next = newinstr( op, operand1, operand2, dest );
      t->code->end = t->code->end->next;
    } else if ( tmpcode != NULL && tmpcode2 != NULL ) {
      t->code = tmpcode;
      t->code->end->next = tmpcode2->start;
      t->code->end = tmpcode2->end;
      t->code->end->next = newinstr( op, operand1, operand2, dest );
      t->code->end = t->code->end->next;
    }
    //print_code( t );
    break;    
  case Assg:
    printf( "Generating code for assignment...\n" );
    tmpcode = code_gen( stAssg_Lhs(t) );
    if ( tmpcode != NULL ) { 
      t->code = tmpcode;
      tmpcode = code_gen( stAssg_Rhs(t) );
      t->code->end->next = tmpcode->start;
      t->code->end = t->code->end->next;
    } else { // lhs is a variable
      t->code = code_gen( stAssg_Rhs(t) );
    }
    op = TAC_Assg;
    operand1 = (address *) zalloc( sizeof(address) );
    operand1->atype = AT_StRef;
    operand1->val.stptr = stAssg_Rhs(t)->place;
    operand2 = NULL;
    dest = (address *) zalloc( sizeof(address) );
    dest->atype = AT_StRef;
    dest->val.stptr = stAssg_Lhs(t)->place;
    t->code->end->next = newinstr( op, operand1, operand2, dest );
    t->code->end = t->code->end->next;
    //print_code( t );
    break;
  case STnodeList:
    printf( "Generating code for statment list...\n" );
    t->code = code_gen( stList_Head(t) );
    for ( tntmp = stList_Rest( t ); tntmp != NULL;
	  tntmp = stList_Rest(tntmp) ) {
      printf( "Generating code for statment list...\n" );
      tmpcode = code_gen( stList_Head(tntmp) );
      t->code->end->next = tmpcode->start;
      t->code->end = tmpcode->end;
    }
    //    print_code( t );
    break;
  case Return:
    printf( "Returning....\n" );
    t->code = (three_addr_code *) zalloc( sizeof(three_addr_code) );
    op = TAC_Return;
    operand1 = NULL;
    operand2 = NULL;
    dest = NULL;
    t->code->start = newinstr( op, operand1, operand2, dest );
    t->code->end = t->code->start;
    break;
  }

  return t->code;
}
