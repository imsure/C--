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

def fill_table( k, instr, rs, ws, brs, others, header ):
    if header.endswith( '-O1' ):
        v = stats_with_O1[ k ]
    if header.endswith( '-O2' ):
        v = stats_with_O2[ k ]
    if header.endswith( '-O1O2' ):
        v = stats_with_O1O2[ k ]

    perc = ( int(instr) - int(v[0]) ) / float( instr )
    v_instr = '{0} ({1:.1f}%)'.format(v[0], perc*100);

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

    ## Print stats into a table.
    for k in sorted( stats_without_O1O2 ):
        v = stats_without_O1O2[ k ]
        print( '{0:14} {1:14} {2:14} {3:14} {4:14} {5:8}'.format(k, 'instructions',
                                                               'reads', 'writes',
                                                               'branches', 'other') )
        print( '{0:14} {1:14} {2:14} {3:14} {4:14} {5:8}'.format('without-O1-O2', v[0], v[1],
                                                               v[2], v[3], v[4]) )

        fill_table( k+'-O1', v[0], v[1], v[2], v[3], v[4], 'with-O1' )
        fill_table( k+'-O2', v[0], v[1], v[2], v[3], v[4], 'with-O2' )
        fill_table( k+'-O1O2', v[0], v[1], v[2], v[3], v[4], 'with-O1O2' )

        # total_cmp = int(v[0]) - int(v2[0])
        # read_cmp = int(v[1]) - int(v2[1])
        # write_cmp = int(v[2]) - int(v2[2])
        # branch_cmp = int(v[3]) - int(v2[3])
        # other_cmp = int(v[4]) - int(v2[4])
        # print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format('# Dropped', str(total_cmp), str(read_cmp),
        #                                                        str(write_cmp), str(branch_cmp), str(other_cmp)) )
        
        print( '\n' )

## The main function.
def main():
    performance()

if __name__ == '__main__':
    main()
