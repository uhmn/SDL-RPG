#pragma once
double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double distance3D(double x1, double y1, double z1, double x2, double y2, double z2) {
	return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)) + ((z1 - z2) * (z1 - z2)));
}

double grav (double x1, double y1, double x2, double y2, double m1, double m2, double gra) {
	return ((m1 * m2) / (distance(x1, y1, x2, y2) * distance(x1, y1, x2, y2))) * gra;
}

double grav3D(double x1, double y1, double z1, double x2, double y2, double z2, double m1, double m2, double gra) {
	return ((m1 * m2) / (distance3D(x1, y1, z1, x2, y2, z2))) * gra;
}
/*
void doVelocity (Entity& i, float step) {
	i.xl = i.xl + (i.vx * step);
	i.yl = i.yl + (i.vy * step);
	i.zl = i.zl + (i.vz * step);
}
void doGravity (Entity& i, Entity& i2, double gra, float step) {
	float theta = atan2(i2.yl - i.yl, i2.xl - i.xl);
	float F = grav (i.xl, i.yl, i2.xl, i2.yl, i.mass, i2.mass, gra);
	i.vx = i.vx + ((F / i.mass) * cos(theta) * step);
	i.vy = i.vy + ((F / i.mass) * sin(theta) * step);
	i2.vx = i2.vx + ((F / i2.mass) * cos(theta + 3.14159) * step);
	i2.vy = i2.vy + ((F / i2.mass) * sin(theta + 3.14159) * step);
}

void doGravity3D(Entity& i, Entity& i2, double gra, float step) {
	float horz = atan2(i2.zl - i.zl, i2.xl - i.xl);
	float vert = atan2(i2.yl - i.yl, i2.xl - i.xl);
	double D = distance3D(i.xl, i.yl, i.zl, i2.xl, i2.yl, i2.zl);
	double F = ((i.mass * i2.mass) / (D*D)) * gra;
	i.vx = i.vx + ((F / i.mass) * cos(horz) * sin(vert) * step);
	i.vy = i.vy + ((F / i.mass) * sin(horz) * sin(vert) * step);
	i.vz = i.vz + ((F / i.mass) * cos(horz) * step);
	i2.vx = i2.vx + (((F * -1) / i2.mass) * cos(horz) * sin(vert) * step);
	i2.vy = i2.vy + (((F * -1) / i2.mass) * sin(horz) * sin(vert) * step);
	i2.vz = i2.vz + (((F * -1) / i2.mass) * cos(horz) * step);
}
*/