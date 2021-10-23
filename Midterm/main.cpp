#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

struct solutionPair
{
	int pOneScore = 0;
	int pTwoScore = 0;
};

int findSolutions(const std::list<int> problem, std::vector<solutionPair>& solution, int i = 0);
solutionPair operator+=(solutionPair& rhs, const solutionPair& lhs);

int main()
{
	std::list<int> problem = { 8,5,14,10,6,8 };
	std::vector<solutionPair> sol;

	std::cout << findSolutions(problem, sol) << std::endl;
	for (const auto& i : sol)
		std::cout << "(" << i.pOneScore << ", " << i.pTwoScore << ")" << ", ";
}

int findSolutions(const std::list<int> problem, std::vector<solutionPair>& solution, int i)
{
	if (problem.size() == 0)
		return solution[i / 2].pOneScore - solution[i / 2].pTwoScore;

	if (problem.size() == 1)
	{
		solution[i] = { problem.front(), 0 };
		solution[i] += solution[(i - 1) / 2];
		return solution[i].pOneScore - solution[i].pTwoScore;
	}

	if (i == 0)
	{
		solution.resize(std::pow(2, (problem.size() + 3) / 2));
		solution[0] = { 0, 0 };

		return findSolutions(problem, solution, 1);
	}
	else
	{
		int left;
		int right;

		int second = *(++problem.begin());
		int secondLast = *std::prev(problem.end(), 2);

		int max = std::max(second, problem.back());
		solution[i] = { problem.front(), max };
		solution[i] += solution[i / 2];
		if (max == problem.back())
			left = findSolutions(std::list<int>(++problem.begin(), --problem.end()), solution, 2 * i + 1);
		else
			left = findSolutions(std::list<int>(std::next(problem.begin(), 2), problem.end()), solution, 2 * i + 1);

		max = std::max(problem.front(), secondLast);
		solution[i + 1] = { problem.back(), max };
		solution[i + 1] += solution[i / 2];
		if (max == problem.front())
			right = findSolutions(std::list<int>(++problem.begin(), --problem.end()), solution, 2 * i + 3);
		else
			right = findSolutions(std::list<int>(problem.begin(), std::prev(problem.end(), 2)), solution, 2 * i + 3);

		return std::max(left, right);
	}

}


solutionPair operator+=(solutionPair& lhs, const solutionPair& rhs)
{
	lhs.pOneScore += rhs.pOneScore;
	lhs.pTwoScore += rhs.pTwoScore;

	return lhs;
}
