CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = ls
OBJS = ls.o print.o cmp.o

# Quy tắc mặc định
all: $(TARGET)

# Liên kết các tệp .o thành file thực thi
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Quy tắc biên dịch từng file .c thành file .o
# Mỗi file .o phụ thuộc vào file .c tương ứng và ls.h
%.o: %.c ls.h
	$(CC) $(CFLAGS) -c $< -o $@

# Dọn dẹp môi trường
clean:
	rm -f $(OBJS) $(TARGET)
