for dim in 8 16 32
do
    # RISC-V loop
    # for riscv_binary in "tests/test-progs/bansal_airlines/hello/hello_riscv64" \
    #               "tests/test-progs/bansal_airlines/row-major/row-major_riscv64" \
    #               "tests/test-progs/bansal_airlines/column-major/column-major_riscv64" \
    #               "tests/test-progs/bansal_airlines/strassen/strassen_riscv64"
    # do
    #     binary=$(basename "$riscv_binary")
    #     build/RISCV/gem5.debug -d "out_bansal/${binary}_${dim}_out" configs/assignments/bansal_airlines.py --cpu RiscvO3CPU --binary "$riscv_binary" --argv "$dim"
    # done

    # # x86 loop
    # for x86_binary in "tests/test-progs/bansal_airlines/hello/hello_x64" \
    #             "tests/test-progs/bansal_airlines/row-major/row-major_x64" \
    #             "tests/test-progs/bansal_airlines/column-major/column-major_x64" \
    #             "tests/test-progs/bansal_airlines/strassen/strassen_x64"
    # do
    #     binary=$(basename "$x86_binary")
    #     build/X86/gem5.debug -d "out_bansal/${binary}_${dim}_out" configs/assignments/bansal_airlines.py --cpu X86O3CPU --binary "$x86_binary" --argv "$dim"
    # done

    # ARM loop
    for arm_binary in "tests/test-progs/bansal_airlines/hello/hello_arm64" \
                "tests/test-progs/bansal_airlines/row-major/row-major_arm64" \
                "tests/test-progs/bansal_airlines/column-major/column-major_arm64" \
                "tests/test-progs/bansal_airlines/strassen/strassen_arm64"
    do
        binary=$(basename "$arm_binary")
        build/ARM/gem5.debug -d "out_bansal/${binary}_${dim}_out" configs/assignments/bansal_airlines.py --cpu ArmO3CPU --binary "$arm_binary" --argv "$dim"
    done
done