PORT=10000

create_database:
	docker start my_little_garden 2> /dev/null || docker run -d -p 27017:27017 --name my_little_garden mongo

install_requirements:
	pip3 install -r requirements.txt

populate_database:
	python3 populate_database.py

run_server:
	ip_address=$$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1' | head -n1); \
	python3 server.py $$ip_address $(PORT)

run_server_local:
	python3 server.py 127.0.0.1 $(PORT) &

run_mock_esp32: run_server_local
	python3 mock_esp32.py $(PORT)

list_docker:
	sudo docker ps -a

start_docker: # only after installed using the create_database entry
	sudo docker start my_little_garden