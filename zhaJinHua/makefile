make_all= chat_ server_ ai_ client_
all:$(make_all)

server_:
	gcc main.c -lpthread -o serv.out
chat_:
	gcc chat.c -o chat.out
ai_:
	gcc ai.c -o ai.out
client_:
	cd cli/ && gcc client.c -o client.out && cp client.out ../../../CVS/tmp/legendOf3Cards/
clean:
	rm *.out cli/*.out