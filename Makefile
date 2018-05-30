TARGET=blink_led

SRC=blink_led.c
SRC+=timer.c
SRC+=hard.c


CC=sdcc
FAMILY=pic14
PROC=16f628a

all: $(TARGET).hex

# $(SRC:.c=.rel): $(SRC)

$(TARGET).hex: $(SRC:.c=.o)
	# Linking objets: $(SRC:.c=.o)
	$(CC) -Wl--map --use-non-free -m$(FAMILY) -p$(PROC) $^
	gpdasm -p$(PROC) -i $(TARGET).hex | head -n 4

%.o: %.c $(SRC)
	$(CC) -c --use-non-free -m$(FAMILY) -p$(PROC) $<

# $(SRC:.c=.hex): $(SRC)
# 	$(CC) --use-non-free -m$(FAMILY) -p$(PROC) $^

clean:
	rm -f $(SRC:.c=.asm) $(SRC:.c=.cod) $(SRC:.c=.hex) $(SRC:.c=.lst) $(SRC:.c=.o) $(SRC:.c=.map)

erase:
	pk2cmd  -P PIC16F628A -X -E

flash:
	pk2cmd -P PIC16F628A -X -M -F blink_led.hex

.PHONY: all clean
