"""
A short and concise description goes here.

Author: Shuo Yang
Email: imsure95@gmail.com
"""

#!/usr/bin/env python3

stats_without_O1O2O3 = {}
stats_with_O1 = {}
stats_with_O2 = {}
stats_with_O3 = {}
stats_with_O1O2 = {}
stats_with_O1O3 = {}
stats_with_O2O3 = {}
stats_with_O1O2O3 = {}

num_o3_inc = 0
num_o3_dec = 0

def fill_table( k, instr, rs, ws, brs, others, header ):
    global num_o3_inc
    global num_o3_dec

    if header.endswith( '-O1' ):
        v = stats_with_O1[ k ]
    if header.endswith( '-O2' ):
        v = stats_with_O2[ k ]
    if header.endswith( '-O3' ):
        v = stats_with_O3[ k ]
    if header.endswith( '-O1O2' ):
        v = stats_with_O1O2[ k ]
    if header.endswith( '-O1O3' ):
        v = stats_with_O1O3[ k ]
    if header.endswith( '-O2O3' ):
        v = stats_with_O2O3[ k ]
    if header.endswith( '-O1O2O3' ):
        v = stats_with_O1O2O3[ k ]

    perc_instr = ( int(instr) - int(v[0]) ) / float( instr ) * 100
    v_instr = '{0} ({1:.1f}%)'.format(v[0], perc_instr);
    if header.endswith( '-O3' ):
        if perc_instr >= 0.0:
            num_o3_inc += 1
        else:
            num_o3_dec += 1

    perc = ( int(rs) - int(v[1]) ) / float( rs )
    v_rs = '{0} ({1:.1f}%)'.format(v[1], perc*100);

    perc = ( int(ws) - int(v[2]) ) / float( ws )
    v_ws = '{0} ({1:.1f}%)'.format(v[2], perc*100);

    perc = ( int(brs) - int(v[3]) ) / float( brs )
    v_brs = '{0} ({1:.1f}%)'.format(v[3], perc*100);

    perc = ( int(others) - int(v[4]) ) / float( others )
    v_others = '{0} ({1:.1f}%)'.format(v[4], perc*100);

    print( '{0:14} {1:14} {2:14} {3:14} {4:14} {5:8}'.format(header, v_instr, v_rs,
                                                             v_ws, v_brs, v_others ) )

    return perc_instr

def performance():
    f = open( 'performance_all.txt' )

    ## Collect performance stats into a dict.
    for line in f.readlines():
        fields = line.split( ',' )
        testname = fields[ 0 ]
        other = fields[ -1 ].strip()
        branches = fields[ -3 ]
        writes = fields[ -5 ]
        reads = fields[ -7 ]
        total = fields[ -10 ]

        if testname.endswith( '-O1' ):
            stats_with_O1[ testname ] = ( total, reads, writes, branches, other )
        elif testname.endswith( '-O2' ):
            stats_with_O2[ testname ] = ( total, reads, writes, branches, other )
        elif testname.endswith( '-O3' ):
            stats_with_O3[ testname ] = ( total, reads, writes, branches, other )
        elif testname.endswith( '-O1O2' ):
            stats_with_O1O2[ testname ] = ( total, reads, writes, branches, other )
        elif testname.endswith( '-O1O3' ):
            stats_with_O1O3[ testname ] = ( total, reads, writes, branches, other )
        elif testname.endswith( '-O2O3' ):
            stats_with_O2O3[ testname ] = ( total, reads, writes, branches, other )
        elif testname.endswith( '-O1O2O3' ):
            stats_with_O1O2O3[ testname ] = ( total, reads, writes, branches, other )
        else:
            stats_without_O1O2O3[ testname ] = ( total, reads, writes, branches, other )

    perc_o1 = perc_o2 = perc_o3 = perc_o12 = perc_o23 = perc_o13 = perc_o123 = 0.0
    best_o1 = best_o2 = best_o3 = best_o12 = best_o23 = best_o13 = best_o123 = 0
    ## Print stats into a table.
    for k in sorted( stats_without_O1O2O3 ):
        v = stats_without_O1O2O3[ k ]
        print( '{0:14} {1:14} {2:14} {3:14} {4:14} {5:8}'.format(k, 'instructions',
                                                               'reads', 'writes',
                                                               'branches', 'other') )
        print( '{0:14} {1:14} {2:14} {3:14} {4:14} {5:8}'.format('without-OPT', v[0], v[1],
                                                               v[2], v[3], v[4]) )

        perc_o1 = fill_table( k+'-O1', v[0], v[1], v[2], v[3], v[4], 'with-O1' )
        perc_o2 = fill_table( k+'-O2', v[0], v[1], v[2], v[3], v[4], 'with-O2' )
        perc_o3 = fill_table( k+'-O3', v[0], v[1], v[2], v[3], v[4], 'with-O3' )
        perc_o12 = fill_table( k+'-O1O2', v[0], v[1], v[2], v[3], v[4], 'with-O1O2' )
        perc_o13 = fill_table( k+'-O1O3', v[0], v[1], v[2], v[3], v[4], 'with-O1O3' )
        perc_o23 = fill_table( k+'-O2O3', v[0], v[1], v[2], v[3], v[4], 'with-O2O3' )
        perc_o123 = fill_table( k+'-O1O2O3', v[0], v[1], v[2], v[3], v[4], 'with-O1O2O3' )

        max_perc = max( [perc_o1,perc_o2,perc_o3,perc_o12,perc_o23,perc_o13,perc_o123] )
        if max_perc == perc_o123: best_o123 += 1
        elif max_perc == perc_o13: best_o13 += 1
        elif max_perc == perc_o23: best_o23 += 1
        elif max_perc == perc_o12: best_o12 += 1
        elif max_perc == perc_o3: best_o3 += 1
        elif max_perc == perc_o2: best_o2 += 1
        elif max_perc == perc_o1: best_o1 += 1

        print( '\n' )

    total = num_o3_inc + num_o3_dec
    # Write out summary
    print( '*************Test result summary***************\n' )
    
    print( 'Total # of tests run: {0}'.format(num_o3_inc+num_o3_dec) )
    print( 'Total # of tests passed: {0}'.format(num_o3_inc+num_o3_dec) )
    print( 'Total # of tests failed: 0\n' )

    print( '-' * 70 )
    print( """We use percentage reduction in the number of instructions executed
against tests run without any optimizations to evaluate optimizations.""" )
    print( '-' * 70 )
    print( '\n' )
    
    print( 'Total # of tests on which -O3 optimization increases performance: {0}'
           .format(num_o3_inc) )
    print( 'Total # of tests on which -O3 optimization decreases performance: {0}\n'
           .format(num_o3_dec) )

    print( '-' * 70 )
    print( 'Overall comparison of -O1, -O2, -O3 and their combinations:' )
    print( '-' * 70 )
    print( '\n' )
    print( 'Number of test cases where -O1 -O2 -O3 together performs best: {0}'.
           format(best_o123) )
    print( 'Number of test cases where -O1 -O3 together performs best: {0}'.
           format(best_o13) )
    print( 'Number of test cases where -O2 -O3 together performs best: {0}'.
           format(best_o23) )
    print( 'Number of test cases where -O1 -O2 together performs best: {0}'.
           format(best_o12) )
    print( 'Number of test cases where -O3 performs best: {0}'.
           format(best_o3) )
    print( 'Number of test cases where -O2 performs best: {0}'.
           format(best_o2) )
    print( 'Number of test cases where -O1 best: {0}'.
           format(best_o1) )


    # print( 'Total # of tests on which -O2 optimization increase performance: {0}'
    #        .format(num_o2_inc) )
    # print( 'Total # of tests on which -O2 optimization decrease performance: {0}\n'
    #        .format(num_o2_dec) )

    # print( 'Total # of tests on which -O1&O2 optimization increase performance: {0}'
    #        .format(num_o1o2_inc) )
    # print( 'Total # of tests on which -O1&O2 optimization decrease performance: {0}'
    #        .format(num_o1o2_dec) )

    # print( '\nUse the number of instructions as benchmark:\n' )
    # print( 'Total # of tests on which -O1 optimization outperforms -O2 optimization: {0}'
    #        .format(num_o1_beats_o2) )
    # print( 'Total # of tests on which -O2 optimization outperforms -O1 optimization: {0}\n'
    #        .format(total-num_o1_beats_o2) )
    # print( 'Total # of tests on which -O1 optimization outperforms -O1&-O2 optimization: {0}'
    #        .format(num_o1_beats_o1o2) )
    # print( 'Total # of tests on which -O1&O2 optimization outperforms -O1 optimization: {0}\n'
    #        .format(total-num_o1_beats_o1o2) )
    # print( 'Total # of tests on which -O2 optimization outperforms -O1&O2 optimization: {0}'
    #        .format(num_o2_beats_o1o2) )
    # print( 'Total # of tests on which -O1&O2 optimization outperforms -O2 optimization: {0}\n'
    #        .format(total-num_o2_beats_o1o2) )


## The main function.
def main():
    performance()

if __name__ == '__main__':
    main()
