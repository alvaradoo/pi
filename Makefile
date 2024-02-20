# Your choices of compilers.
iCC 	= 	icc
gCC 	=   gcc

# Add your choice of flags.
iCFLAGS   =   -qopenmp
gCFLAGS   =   -fopenmp

# Pinpoint all targets. 
TARGETS = pi_serial_icc pi_serial_gcc pi_spmd_icc pi_spmd_gcc pi_spmd_padded_icc pi_spmd_padded_gcc pi_spmd_critical_icc pi_spmd_critical_gcc pi_spmd_loop_icc pi_spmd_loop_gcc

.PHONY : all
all : $(TARGETS)

.PHONY : default
default : all

pi_serial_icc: 	pi_serial.c 
			   	${iCC} -o pi_serial_icc pi_serial.c ${iCFLAGS}

pi_serial_gcc: 	pi_serial.c 
				${gCC} -o pi_serial_gcc pi_serial.c ${gCFLAGS}

pi_spmd_icc: 	pi_spmd.c 
			   	${iCC} -o pi_spmd_icc pi_spmd.c ${iCFLAGS}

pi_spmd_gcc: 	pi_spmd.c 
				${gCC} -o pi_spmd_gcc pi_spmd.c ${gCFLAGS}

pi_spmd_padded_icc: 	pi_spmd_padded.c 
			   			${iCC} -o pi_spmd_padded_icc pi_spmd_padded.c ${iCFLAGS}

pi_spmd_padded_gcc: 	pi_spmd_padded.c 
						${gCC} -o pi_spmd_padded_gcc pi_spmd_padded.c ${gCFLAGS}

pi_spmd_critical_icc: 	pi_spmd_critical.c 
			   			${iCC} -o pi_spmd_critical_icc pi_spmd_critical.c ${iCFLAGS}

pi_spmd_critical_gcc: 	pi_spmd_critical.c 
						${gCC} -o pi_spmd_critical_gcc pi_spmd_critical.c ${gCFLAGS}

pi_spmd_loop_icc: 	pi_spmd_loop.c 
			   			${iCC} -o pi_spmd_loop_icc pi_spmd_loop.c ${iCFLAGS}

pi_spmd_loop_gcc: 	pi_spmd_loop.c 
						${gCC} -o pi_spmd_loop_gcc pi_spmd_loop.c ${gCFLAGS}

clean:
	rm -f pi_serial_icc
	rm -f pi_serial_gcc
	rm -f pi_spmd_icc
	rm -f pi_spmd_gcc
	rm -f pi_spmd_padded_icc
	rm -f pi_spmd_padded_gcc
	rm -f pi_spmd_critical_icc
	rm -f pi_spmd_critical_gcc
	rm -f pi_spmd_loop_icc
	rm -f pi_spmd_loop_gcc
