CC = clang
CFLAGS = -Iinclude $(shell pkg-config --cflags libsodium)
LDLIBS = $(shell pkg-config --libs libsodium)

SRC = src/main.c src/menu.c src/password.c src/linked_list.c src/hash_table.c src/storage.c	src/encryption.c

TARGET = password-manager

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)	$(LDLIBS)

clean:
	rm -f $(TARGET)