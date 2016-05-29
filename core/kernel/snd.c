/*
 * File: snd.c
 * Author: Fabien Siron, From osdev
 */

#include <kernel/pyr0.h>
#include <kernel/pit.h>

#include <asm/io.h>

static void play_sound(u32 nFrequence) {
	u32 Div;
	u8 tmp;

	//Set the PIT to the desired frequency
	Div = 1193180 / nFrequence;
	outb(0x43, 0xb6);
	outb(0x42, (u8) (Div) );
	outb(0x42, (u8) (Div >> 8));

	//And play the sound using the PC speaker
	tmp = inb(0x61);
	if (tmp != (tmp | 3)) {
		outb(0x61, tmp | 3);
	}
}

//make it shutup
static void nosound() {
	u8 tmp = inb(0x61) & 0xFC;

	outb(0x61, tmp);
}

//Make a beep
void beep() {
	play_sound(1000);
	pit_wait(100);
	nosound();
}

void long_beep() {
	play_sound(1000);
	pit_wait(500);
	nosound();
}

void sos() {
	int i;
	for (i = 0; i < 9; ++i) {
		if (i >= 3 && i < 6) {
			long_beep();
		} else {
			beep ();
		}
		pit_wait(100);
	}
}
