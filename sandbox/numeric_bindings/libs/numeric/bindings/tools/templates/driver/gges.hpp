$TEMPLATE[gges.all.min_size_work.args]
N
$TEMPLATE[gges.real.min_size_work]
return std::max( 1, 8*n + 16 );
$TEMPLATE[gges.complex.min_size_work]
return std::max( 1, 2*n );
$TEMPLATE[gges.all.min_size_bwork.args]
N, SORT
$TEMPLATE[gges.all.min_size_bwork]
if ( sort == 'N' )
    return 0;
else
    return n;
$TEMPLATE[end]
