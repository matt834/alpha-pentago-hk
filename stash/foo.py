def all_possible_move_strings():
	movestrings = []
	for col in ["a", "b", "c", "d", "e", "f"]:
		for row in range(1, 7):
			for square in range(4):
				movestrings.append(f"{col}{row}{square}L")
				movestrings.append(f"{col}{row}{square}R")
	print(len(movestrings))
	print('", "'.join(movestrings))


def print_board_indices():
	s = ""
	for i in range(6):
		r = ""
		for j in range(6):
			r += f"{(j + 6*i):02} "
		s = r + "\n" + s

	print(s)


if __name__ == "__main__":
	print_board_indices()