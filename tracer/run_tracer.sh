PIN_SOURCE="/localdisk/pin-3.11-97998-g7ecce2dac-gcc-linux"
PIN_OBJ_SOURCE="$PIN_SOURCE/source/tools"
BENCH_BIN="../trace_src/bin"
TRACE_DIR="./"
PIN_SMPL_SOURCE="$PIN_SOURCE/tools/SimpleExamples/obj-intel64"
# $PIN_SOURCE/pin -ifeellucky -t $PIN_OBJ_SOURCE/SimpleExamples/obj-intel64/icount.so -- $1
# $PIN_SOURCE/pin -ifeellucky -t obj-intel64/champsim_tracer.so -o $1_trace.champsim -s 100000 -t 200000 -- $1

# iterate all polybenchmarks
echo "Instrumenting $1"
$PIN_SOURCE/pin -ifeellucky -t obj-intel64/champsim_tracer.so -o $1.trace.champsim -s $2 -t $3 -- $BENCH_BIN/$1
echo "Compress $1 in .gz format"
gzip -f $1.trace.champsim
echo "Copy the results to $TRACE_DIR"
cp $1.trace.champsim.gz $TRACE_DIR/
