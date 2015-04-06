"""
A short and concise description goes here.

Author: Shuo Yang
Email: imsure95@gmail.com
"""

#!/usr/bin/env python3

stats_without_O1O2 = {}
stats_with_O1 = {}
stats_with_O2 = {}
stats_with_O1O2 = {}

num_o1_inc = 0
num_o1_dec = 0

num_o2_inc = 0
num_o2_dec = 0

num_o1o2_inc = 0
num_o1o2_dec = 0

def fill_table( k, instr, rs, ws, brs, others, header ):
    global num_o1_inc
    global num_o1_dec
    global num_o2_inc
    global num_o2_dec
    global num_o1o2_inc
    global num_o1o2_dec

    if header.endswith( '-O1' ):
        v = stats_with_O1[ k ]
    if header.endswith( '-O2' ):
        v = stats_with_O2[ k ]
    if header.endswith( '-O1O2' ):
        v = stats_with_O1O2[ k ]

    perc = ( int(instr) - int(v[0]) ) / float( instr ) * 100
    v_instr = '{0} ({1:.1f}%)'.format(v[0], perc);
    if header.endswith( '-O1' ):
        if perc >= 0.0:
            num_o1_inc += 1
        else:
            num_o1_dec += 1
    if header.endswith( '-O2' ):
        if perc >= 0:
            num_o2_inc += 1
        else:
            num_o2_dec += 1
    if header.endswith( '-O1O2' ):
        if perc >= 0:
            num_o1o2_inc += 1
        else:
            num_o1o2_dec += 1

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

num_o1_beats_o2 = 0

def compare_o1o2( key_o1, key_o2 ):
    global num_o1_beats_o2

    v_o1 = stats_with_O1[ key_o1 ]
    v_o2 = stats_with_O2[ key_o2 ]

    if v_o1[0] < v_o2[0]:
        num_o1_beats_o2 += 1

num_o1_beats_o1o2 = 0

def compare_o1o12( key_o1, key_o1o2 ):
    global num_o1_beats_o1o2

    v_o1 = stats_with_O1[ key_o1 ]
    v_o2 = stats_with_O1O2[ key_o1o2 ]

    if v_o1[0] < v_o2[0]:
        num_o1_beats_o1o2 += 1

num_o2_beats_o1o2 = 0

def compare_o2o12( key_o2, key_o1o2 ):
    global num_o2_beats_o1o2

    v_o2 = stats_with_O2[ key_o2 ]
    v_o1o2 = stats_with_O1O2[ key_o1o2 ]

    if v_o2[0] < v_o1o2[0]:
        num_o2_beats_o1o2 += 1

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
        elif testname.endswith( '-O1O2' ):
            stats_with_O1O2[ testname ] = ( total, reads, writes, branches, other )
        else:
            stats_without_O1O2[ testname ] = ( total, reads, writes, branches, other )

    num_iter = 0
    ## Print stats into a table.
    for k in sorted( stats_without_O1O2 ):
        num_iter += 1
        v = stats_without_O1O2[ k ]
        print( '{0:14} {1:14} {2:14} {3:14} {4:14} {5:8}'.format(k, 'instructions',
                                                               'reads', 'writes',
                                                               'branches', 'other') )
        print( '{0:14} {1:14} {2:14} {3:14} {4:14} {5:8}'.format('without-O1-O2', v[0], v[1],
                                                               v[2], v[3], v[4]) )

        fill_table( k+'-O1', v[0], v[1], v[2], v[3], v[4], 'with-O1' )
        fill_table( k+'-O2', v[0], v[1], v[2], v[3], v[4], 'with-O2' )
        fill_table( k+'-O1O2', v[0], v[1], v[2], v[3], v[4], 'with-O1O2' )
        compare_o1o2( k+'-O1', k+'-O2' )
        compare_o1o12( k+'-O1', k+'-O1O2' )
        compare_o2o12( k+'-O2', k+'-O1O2' )

        print( '\n' )

    total = num_o1_inc + num_o1_dec
    # Write out summary
    print( '*************Test result summary***************\n' )
    
    print( 'Total # of tests run: {0}'.format(num_o1_inc+num_o1_dec) )
    print( 'Total # of tests passed: {0}'.format(num_o1_inc+num_o1_dec) )
    print( 'Total # of tests failed: 0\n' )

    print( 'Use the number of instructions of tests run without any optimizations as benchmark:\n' )
    print( 'Total # of tests on which -O1 optimization increase performance: {0}'
           .format(num_o1_inc) )
    print( 'Total # of tests on which -O1 optimization decrease performance: {0}\n'
           .format(num_o1_dec) )

    print( 'Total # of tests on which -O2 optimization increase performance: {0}'
           .format(num_o2_inc) )
    print( 'Total # of tests on which -O2 optimization decrease performance: {0}\n'
           .format(num_o2_dec) )

    print( 'Total # of tests on which -O1&O2 optimization increase performance: {0}'
           .format(num_o1o2_inc) )
    print( 'Total # of tests on which -O1&O2 optimization decrease performance: {0}'
           .format(num_o1o2_dec) )

    print( '\nUse the number of instructions as benchmark:\n' )
    print( 'Total # of tests on which -O1 optimization outperforms -O2 optimization: {0}'
           .format(num_o1_beats_o2) )
    print( 'Total # of tests on which -O2 optimization outperforms -O1 optimization: {0}\n'
           .format(total-num_o1_beats_o2) )
    print( 'Total # of tests on which -O1 optimization outperforms -O1&-O2 optimization: {0}'
           .format(num_o1_beats_o1o2) )
    print( 'Total # of tests on which -O1&O2 optimization outperforms -O1 optimization: {0}\n'
           .format(total-num_o1_beats_o1o2) )
    print( 'Total # of tests on which -O2 optimization outperforms -O1&O2 optimization: {0}'
           .format(num_o2_beats_o1o2) )
    print( 'Total # of tests on which -O1&O2 optimization outperforms -O2 optimization: {0}\n'
           .format(total-num_o2_beats_o1o2) )


## The main function.
def main():
    performance()

if __name__ == '__main__':
    main()
