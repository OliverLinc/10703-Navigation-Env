#include "map.h"

using namespace nel;

struct item_position_printer { };

template<typename Stream>
inline bool print(const item_position& item_pos, Stream& out, const item_position_printer& printer) {
	return print(item_pos.location, out);
}

float intensity(const position& world_position, unsigned int type) {
	return -2.0f;
}

float interaction(
		const position& first_position, const position& second_position,
		unsigned int first_type, unsigned int second_type)
{
	uint64_t squared_length = (first_position - second_position).squared_length();
	if (squared_length < 40)
		return 0.0;
	else if (squared_length < 200)
		return -20.0;
	else return 0.0;
}

int main(int argc, const char** argv) {
	static constexpr int n = 32;
	auto m = map<n, 1>(10, intensity, interaction);

	patch<n, 1>* neighborhood[4];
	position neighbor_positions[4];
	m.get_fixed_neighborhood({0, 0}, neighborhood, neighbor_positions);

	array<item_position> item_positions(128);
	m.get_items({-2*n, -2*n}, {2*n - 1, 2*n - 1}, item_positions);
	item_position_printer printer;
	print(item_positions, stdout, printer); print('\n', stdout);
	fflush(stdout);
	return EXIT_SUCCESS;
}
