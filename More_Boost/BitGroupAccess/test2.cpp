struct s {
	unsigned dummy1 : 2;
	unsigned foo	: 1;
	unsigned dummy2	: 1;
	unsigned bar	: 4;
	unsigned dummy3	: 1;
	unsigned baz	: 1;
	unsigned dummy4 : 6;
};

void xxx() {
	extern struct s ov;
	ov.bar= 1u;
}
int yyy() {
	extern struct s ov;
	return ov.bar;
}
