def generate_neighbours(path):

    neighbour_dec = {}

    with open(path) as f:
        for line in f:
            if line.split()[0] not in neighbour_dec:
                _list = list()
                _list.append([line.split()[1], line.split()[2]])
                neighbour_dec[line.split()[0]] = _list
            else:
                neighbour_dec[line.split()[0]].append(
                    [line.split()[1], line.split()[2]]
                )
            if line.split()[1] not in neighbour_dec:
                _list = list()
                _list.append([line.split()[0], line.split()[2]])
                neighbour_dec[line.split()[1]] = _list
            else:
                neighbour_dec[line.split()[1]].append(
                    [line.split()[0], line.split()[2]]
                )

    return neighbour_dec


def first_solution(path, neighbour_dec):

    with open(path) as f:
        s_node = f.read(1)
    e_node = s_node

    f_solution = []

    decision = s_node

    first_solution_dec = 0
    while decision not in f_solution:
        minim = 10000
        for k in neighbour_dec[decision]:
            if int(k[1]) < int(minim) and k[0] not in f_solution:
                minim = k[1]
                best_node = k[0]

        f_solution.append(decision)
        f_solution_dec = f_solution_dec + int(minim)
        decision = b_node

    f_solution.append(e_node)

    position = 0
    for k in neighbour_dec[f_solution[-2]]:
        if k[0] == s_node:
            break
        position += 1

    first_solution_dec = (
        first_solution_dec
        + int(neighbour_dec[f_solution[-2]][position][1])
        - 10000
    )
    return f_solution, first_solution_dec


def generate_dec_data(solution, neighbour_dec):

    n_solution = []

    for n in solution[1:-1]:
        idx1 = solution.index(n)
        for kn in solution[1:-1]:
            idx2 = solution.index(kn)
            if n == kn:
                continue

            _tmp = copy.deepcopy(solution)
            _tmp[idx1] = kn
            _tmp[idx2] = n

            decision = 0

            for k in _tmp[:-1]:
                next_node = _tmp[_tmp.index(k) + 1]
                for i in neighbour_dec[k]:
                    if i[0] == next_node:
                        decision = decision + int(i[1])
            _tmp.append(decision)

            if _tmp not in n_solution:
                n_solution.append(_tmp)

    indexOfLastItemInTheList = len(n_solution[0]) - 1

    n_solution.sort(key=lambda x: x[indexOfLastItemInTheList])
    return n_solution


def tabu_search(f_solution, first_solution_dec, neighbour_dec, iters, size):
    count = 1
    solution = f_solution
    tabu_list = list()
    best_sol = first_solution_dec
    best_solution_ever = solution

    while count <= iters:
        neighbor = generate_dec_data(solution, neighbour_dec)
        index_of_best_solution = 0
        best_solution = neighbor[index_of_best_solution]
        best_sol_index = len(best_solution) - 1

        found = False
        while not found:
            i = 0
            while i < len(best_solution):

                if best_solution[i] != solution[i]:
                    first_exchange_node = best_solution[i]
                    second_exchange_node = solution[i]
                    break
                i = i + 1

            if [first_exchange_node, second_exchange_node] not in tabu_list and [
                second_exchange_node,
                first_exchange_node,
            ] not in tabu_list:
                tabu_list.append([first_exchange_node, second_exchange_node])
                found = True
                solution = best_solution[:-1]
                sol = neighbor[index_of_best_solution][best_sol_index]
                if sol < best_sol:
                    best_sol = sol
                    best_solution_ever = solution
            else:
                index_of_best_solution = index_of_best_solution + 1
                best_solution = neighbor[index_of_best_solution]

        if len(tabu_list) >= size:
            tabu_list.pop(0)

        count = count + 1

    return best_solution_ever, best_sol

def main(args=None):
    neighbour_dec = generate_neighbours(args.File)

    f_solution, first_solution_dec = first_solution(
        args.File, neighbour_dec
    )

    best_sol, best_sol = tabu_search(
        f_solution,
        first_solution_dec,
        neighbour_dec,
        args.Iterations,
        args.Size,
    )

    print(f"Best solution: {best_sol}.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Tabu Search")
    parser.add_argument(
        "-f",
        "--File",
        type=str,
        help="Path to the file containing the data",
        required=True,
    )
    parser.add_argument(
        "-i",
        "--Iterations",
        type=int,
        help="How many iterations the algorithm should perform",
        required=True,
    )
    parser.add_argument("-s", "--Size", type=int, help="Size of the tabu list", required=True)

    main(parser.parse_args())