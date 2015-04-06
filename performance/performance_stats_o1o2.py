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
        print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format(k, 'instructions',
                                                               'reads', 'writes',
                                                               'branches', 'other') )
        print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format('without-O1', v[0], v[1],
                                                               v[2], v[3], v[4]) )
        k2 = k + '-O1'
        v2 = stats_with_O1[ k2 ]
        print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format('with-O1', v2[0], v2[1],
                                                               v2[2], v2[3], v2[4]) )

        k3 = k + '-O2'
        v3 = stats_with_O2[ k3 ]
        print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format('with-O2', v3[0], v3[1],
                                                               v3[2], v3[3], v3[4]) )

        k4 = k + '-O1O2'
        v4 = stats_with_O1O2[ k4 ]
        print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format('with-O1O2', v4[0], v4[1],
                                                               v4[2], v4[3], v4[4]) )

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
