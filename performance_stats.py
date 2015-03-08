"""
A short and concise description goes here.

Author: Shuo Yang
Email: imsure95@gmail.com
"""

#!/usr/bin/env python3

stats_without_O1 = {}
stats_with_O1 = {}

def performance():
    f = open( 'performance.txt' )

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
        else:
            stats_without_O1[ testname ] = ( total, reads, writes, branches, other )

    ## Print stats into a table.
    for k in sorted( stats_without_O1 ):
        v = stats_without_O1[ k ]
        print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format(k, 'instructions',
                                                                     'reads', 'writes',
                                                                     'branches', 'other') )
        print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format('without-O1', v[0], v[1],
                                                               v[2], v[3], v[4]) )
        k2 = k + '-O1'
        v2 = stats_with_O1[ k2 ]
        print( '{0:14} {1:12} {2:6} {3:6} {4:10} {5:8}'.format('with-O1', v2[0], v2[1],
                                                               v2[2], v2[3], v2[4]) )

        total_cmp = round( (float(v[0]) - float(v2[0])) / float(v[0]), 2 )
        read_cmp = round( (float(v[1]) - float(v2[1])) / float(v[1]), 2 )
        write_cmp = round((float(v[2]) - float(v2[2])) / float(v[2]), 2 )
        branch_cmp = round((float(v[3]) - float(v2[3])) / float(v[3]), 2 )
        other_cmp = round((float(v[4]) - float(v2[4])) / float(v[4]), 2 )
        print( '{0:14} {1:1.0%} {2:12.0%} {3:6.0%} {4:6.0%} {5:10.0%}'.format('Dropped by', total_cmp, read_cmp,
                                                                              write_cmp, branch_cmp, other_cmp) )
        
        print( '\n' )

    
## The main function.
def main():
    performance()

if __name__ == '__main__':
    main()
