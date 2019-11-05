PIN_SOURCE="/localdisk/pin-3.11-97998-g7ecce2dac-gcc-linux"
PIN_OBJ_SOURCE="$PIN_SOURCE/source/tools"
BENCH_BIN="/localdisk/CARL/LFUSimulator/trace_src/bin"
TRACE_DIR="/localdisk/CARL/ChampSim_CRC2_ver2.0/ChampSim_CRC2/trace"
PIN_SMPL_SOURCE="$PIN_SOURCE/source/tools/SimpleExamples/obj-intel64"
for prog in $(ls $BENCH_BIN); do
    echo "$prog";
    $PIN_SOURCE/pin -ifeellucky -t $PIN_SMPL_SOURCE/icount.so -- $BENCH_BIN/$prog;
done

