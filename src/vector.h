typedef struct {
	float x, y, z;
}vector;

vector add(vector, vector);
vector sub(vector, vector);
vector mult(vector, vector);
vector cross(vector, vector);
float dot(vector, vector);
