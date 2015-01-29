all: sync_tcp_client sync_tcp_server async_tcp_server async_tcp_client
	@echo DONE
async_tcp_server: async_tcp_server.cpp
	g++ async_tcp_server.cpp -lpthread -lboost_system -o $@
async_tcp_client: async_tcp_client.cpp
	g++ async_tcp_client.cpp -lpthread -lboost_system -o $@
sync_tcp_client: sync_tcp_client.cpp
	g++ sync_tcp_client.cpp -lpthread -lboost_system -o $@
sync_tcp_server: sync_tcp_server.cpp
	g++ sync_tcp_server.cpp -lpthread -lboost_system -o $@
