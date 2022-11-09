BUILD_DIR = build

permission_management: clean_up
	@for f in $(shell ls ${BUILD_DIR}); do chmod 700 ./${BUILD_DIR}/$${f} ; done

clean_up: executables
	rm ${BUILD_DIR}/*.o

executables: client.o client_handlers.o server.o server_handlers.o 
	gcc ${BUILD_DIR}/server.o ${BUILD_DIR}/handlers_serv.o -o ${BUILD_DIR}/server && gcc ${BUILD_DIR}/client.o ${BUILD_DIR}/handlers_cli.o -o ${BUILD_DIR}/client  

client.o: client/client.c client/handlers_cli.h shared/serv_cli_fifo.h
	gcc -c client/client.c -o build/client.o

client_handlers.o: client/handlers_cli.c client/handlers_cli.h shared/serv_cli_fifo.h
	gcc -c client/handlers_cli.c -o build/handlers_cli.o

server.o: server/server.c server/handlers_serv.h shared/serv_cli_fifo.h
	gcc -c server/server.c -o build/server.o

server_handlers.o: server/handlers_serv.c server/handlers_serv.h shared/serv_cli_fifo.h
	gcc -c server/handlers_serv.c -o build/handlers_serv.o