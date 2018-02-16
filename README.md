# nco-test
NCO test suite

## Example usage

```
./nco_test -p /usr/local/bin -f /home/pvicente/nco/data/in_grp.nc -v
TESTING /usr/local/bin/ncks -C --trd -g g6g1 -v area /home/pvicente/nco/data/in_grp.nc PASSED
OUTPUT
/g6/g6g1/area
area: type NC_FLOAT, 1 dimension, 0 attributes, compressed? no, chunked? no, packed? no
area size (RAM) = 2*sizeof(NC_FLOAT) = 2*4 = 8 bytes
area dimension 0: /lat, size = 2 NC_FLOAT (Coordinate is /lat)

/g6/g6g1/area
lat[0]=-90 area[0]=40 (no units)
lat[1]=90 area[1]=50 (no units)
```

