default: par

par:
	@echo '************  COMPILANDO O CODIGO PARALELO ************'
	
	/usr/local/berkeley_upc/bin/upcc parallel/correlation.c --network=smp -o smp
	
	/usr/local/berkeley_upc/bin/upcc parallel/correlation.c --network=udp -o udp

	/usr/local/berkeley_upc/bin/upcc parallel/correlation.c --network=mpi -o mpi
	
	@echo '**************************************************'

	@echo 'Para executar cada versão com 4 threads:'
	@echo 'make run-smp'
	@echo 'make run-udp' 
	@echo 'make run-mpi'
	@echo 'Ou é possível executar manualmente:'
	@echo 'upcrun -n 4 ./smp'
	@echo 'upcrun -n 4 -localhost ./udp'
	@echo 'upcrun -n 4 ./mpi'

	@echo '**************************************************'

seq: 
	gcc -O3 -I utilities -I sequential utilities/polybench.c sequential/correlation.c -DPOLYBENCH_TIME -o sequential_time -lm


run-smp:
	/usr/local/berkeley_upc/bin/upcrun -n 4 ./smp

run-udp:
	/usr/local/berkeley_upc/bin/upcrun -n 4 -localhost ./udp

run-mpi:
	/usr/local/berkeley_upc/bin/upcrun -n 4 ./mpi


clean:
	rm -f symm_time