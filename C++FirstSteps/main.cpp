//
//  main.cpp
//  C++FirstSteps
//
//  Created by Benjamin DOMERGUE on 06/10/12.
//  Copyright (c) 2012 Benjamin DOMERGUE. All rights reserved.
//

#include <iostream>
#include <ios>
#include <iomanip>

#include <string>
#include <sstream>

#include <vector>
#include <algorithm>

using namespace std;

#pragma mark - Chapitre 1 & 2 

void say_greetings_to(string name, int padding)
{
	cout << endl;
	const int totalRow = 1 + 2 * padding + 2;
	const string greetings = "Greetings to you, " + name + "!";
	for (int row = 0; row != totalRow; ++row)
	{
		const double lineSize = greetings.size() + 2 * (padding + 1);
		if(row == padding + 1)
		{
			string greetingsPadding = string(padding, ' ');
			cout << "o" + greetingsPadding + greetings + greetingsPadding + "o" << endl;
		}
		else
		{
			if(row == 0 || row == totalRow - 1)
			{
				string outlines(lineSize, 'o');
				cout << outlines << endl;
			}
			else
			{
				string spaces(lineSize - 2, ' ');
				cout << "o" + spaces + "o" << endl;
			}
		}
	}
	cout << endl;
}

void draw_rectangle(int width, int height)
{
	for(int row = 0; row != height; ++row)
	{
		for(int column = 0; column != width; ++column)
		{
			if(row == 0 || row == height - 1 || column == 0 || column == width - 1)
			{
				cout << "#";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}

void draw_square(int width)
{
	draw_rectangle(width, width);
}

void draw_triangle(int height)
{
	for(int row = 0; row <= height; ++row)
	{
		int leftPadding = height - row - 1;
		if(row == 0)
		{
			cout << string(leftPadding, ' ') << ".";
		}
		else if(row != height)
		{
			int middleSpace = row * 2 - 1;
			cout << string(leftPadding, ' ') << "/" << string(middleSpace, ' ') << "\\";
		}
		else
		{
			cout << string(height * 2 - 1, '-');
		}
		cout << endl;
	}
}

#pragma mark - Chapitre 3

void input_doubles(vector<double> &numbers)
{
	double input = 0;
	while(cin >> input)
	{
		numbers.push_back(input);
	}
}

typedef std::vector<double>::size_type double_vector_size;
double vector_median(vector<double> numbers)
{
	double_vector_size size = numbers.size();
	if(size != 0)
	{
		sort(numbers.begin(), numbers.end());
		
		double_vector_size middle = size / 2;
		return size % 2 == 0 ? ((numbers[middle] + numbers[middle - 1]) / 2) : numbers[middle];
	}
	else
	{
		throw domain_error("cannot calculate median of empty vector");
	}
}

void calculate_median()
{
	cout << "Enter numbers to calculate median of: ";
	
	vector<double> numbers;
	input_doubles(numbers);
	
	double median = vector_median(numbers);
	
	streamsize defaultPrecision = cout.precision();
	cout << "Median is " << setprecision(3) << median << setprecision((int)defaultPrecision) << endl;
}

void vector_quartiles(vector<double> numbers, double &q1, double &q2, double &q3)
{
	double_vector_size size = numbers.size();
	if(size != 0)
	{
		sort(numbers.begin(), numbers.end());
		
		double p = size / 4;
		if(size % 4 == 0)
		{
			q1 = (numbers[p - 1] + numbers[p]) / 2;
			q2 = (numbers[(2 * p) - 1] + numbers[2 * p]) / 2;
			q3 = (numbers[(3 * p) - 1] + numbers[3 * p]) / 2;
		}
		else if((size - 1) % 4 == 0)
		{
			q1 = numbers[p];
			q2 = numbers[2 * p];
			q3 = numbers[3 * p];
			
		}
		else if((size - 2) % 4 == 0)
		{
			q1 = numbers[p];
			q2 = (numbers[(2 * p) + 1] + numbers[2 * p]) / 2;
			q3 = numbers[(3 * p) + 1];
			
		}
		else if((size - 3) % 4 == 0)
		{
			q1 = numbers[p];
			q2 = numbers[(2 * p) + 1];
			q3 = numbers[(3 * p) + 2];
		}
	}
	else
	{
		throw domain_error("cannot calculate median of empty vector");
	}
}

void calculate_quartiles()
{
	cout << "Enter numbers to calculate quartile of: ";
	
	vector<double> numbers;
	input_doubles(numbers);
	
	double q1 = 0, q2 = 0, q3 = 0;
	vector_quartiles(numbers, q1, q2, q3);
	
	streamsize defaultPrecision = cout.precision();
	cout << "Quartiles are: " << setprecision(3) << q1 << ", " << q2 << ", " << q3 << setprecision((int)defaultPrecision) << endl;
}

istream& input_strings(istream& in, vector<string>& strings)
{
	if(in)
	{
		strings.clear();
		
		string input;
		while(in >> input)
		{
			strings.push_back(input);
		}
		in.clear();
	}
	return in;
}

typedef std::vector<string>::size_type string_vector_size;
void count_disctinct_words()
{
	vector<string> strings;
	input_strings(cin, strings);
	
	string_vector_size stringsSize = strings.size();
	if(stringsSize != 0)
	{
		sort(strings.begin(), strings.end());
		
		int i = 0;
		while(i < stringsSize)
		{
			int count = 0;
			string currentWord = strings[i];
			while(i + count < stringsSize)
			{
				if(currentWord == strings[i + count])
				{
					++count;
				}
				else
				{
					break;
				}
			}
			cout << "Count of " << currentWord << " is " << count << endl;
			i += count;
		}
	}
}

void shortest_and_longest_word()
{
	vector<string> strings;
	input_strings(cin, strings);
	
	string_vector_size stringsSize = strings.size();
	if(stringsSize != 0)
	{
		sort(strings.begin(), strings.end());
		
		string shortest = strings[0], longest = strings[0];
		for(int i = 0; i < stringsSize; i++)
		{
			string currentWord = strings[i];
			if(currentWord.size() < shortest.size())
			{
				shortest = currentWord;
			}
			else if(currentWord.size() > longest.size())
			{
				longest = currentWord;
			}
		}
		cout << "The longest word is " << longest << ", the shortest is " << shortest << ".";
	}
}

#pragma mark - Chapitre 4

void print_squares(double top)
{
	string::size_type topStringSize = (ostringstream() << top).str().size();
	
	for(double i = 0; i <= top; ++i)
	{
		cout << setw((int)topStringSize) << i << setw(0) << " " << i * i << endl;
	}
}

double average(const vector<double>& numbers)
{
	vector<double>::size_type numbersCount = numbers.size();
	if(numbersCount != 0)
	{
		double total = 0, count = 0;
		for(vector<double>::size_type i = 0; i < numbersCount; ++i)
		{
			++count;
			total += numbers[i];
		}
		return total / count;
	}
	else
	{
		throw domain_error("Cannot calculate average on empty vector");
	}
}

void calculate_average()
{
	cout << "Enter numbers to calculate average of: " << endl;
	
	double x = 0;
	vector<double> numbers;
	while(cin >> x)
	{
		numbers.push_back(x);
	}
	
	try
	{
		streamsize precision = cout.precision();
		cout << "Average is " << setprecision(3) << average(numbers) << setprecision((int)precision) << endl;
	}
	catch (exception e)
	{
		cout << e.what();
	}
}

#pragma mark - Chapitre 5

#include <cctype>

vector<string> split(const string& input)
{
	vector<string> output;
	string::size_type i = 0, j;
	
	while(i != input.size())
	{
		while(i != input.size() && isspace(input[i]))
		{
			++i;
		}
		
		j = i;
		while(j != input.size() && !isspace(input[j]))
		{
			++j;
		}
		
		if(i != j)
		{
			output.push_back(input.substr(i, j - i));
		}
		i = j;
	}
	return output;
}

vector<string> read_line_then_separe_it()
{
	string s;
	getline(cin, s);
	return split(s);
	
	/* Equals :
	 
	string s;
	while(cin >> s)
	{
		cout << s << endl;
	} */
}

string::size_type longest_word_size(const vector<string>& input)
{
	string::size_type maxlenght = 0;
	for(vector<string>::size_type i = 0; i != input.size(); ++i)
	{
		maxlenght = max(maxlenght, input[i].size());
	}
	return maxlenght;
}

vector<string> frame(const vector<string>& input)
{
	vector<string> output;
	string::size_type longestWordSize = longest_word_size(input);
	string border = string(longestWordSize + 4, '*');
	
	output.push_back(border);
	
	for(vector<string>::const_iterator iterator = input.begin(); iterator != input.end(); ++iterator)
	{
		string framedWord = "* " + *iterator + string(longestWordSize - iterator->size(), ' ') + " *";
		output.push_back(framedWord);
	}
	
	output.push_back(border);
	
	return output;
}

void read_line_then_frame_it()
{
	string s;
	while(getline(cin, s))
	{
		vector<string> framed = frame(split(s));
		for(vector<string>::size_type i = 0; i != framed.size(); ++i)
		{
			cout << framed[i] << endl;
		}
	}
}

vector<string> horizontal_concat(const vector<string>& left, const vector<string>& right)
{
	vector<string> output;
	
	string::size_type leftSizePad = longest_word_size(left) + 1;
	vector<string>::const_iterator i = left.begin(), j = right.begin();
	
	while (i != left.end() || j != right.end())
	{
		string s;
		if(i != left.end())
		{
			s = *i++;
		}
		
		s += string(leftSizePad - s.size(), ' ');
		
		if(j != right.end())
		{
			s += *j++;
		}
		
		output.push_back(s);
	}
	return output;
}

void concat_two_character_frames()
{
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	
	vector<string> words = split(s1);
	vector<string> framedWords = frame(split(s2));
	
	vector<string> concated = horizontal_concat(words, framedWords);
	for(vector<string>::size_type i = 0; i != concated.size(); ++i)
	{
		cout << concated[i] << endl;
	}
}

#pragma mark - Chapitre 6

void back_inserter_test()
{
	vector<int> u(10, 100);
	vector<int> v;
	copy(u.begin(), u.end(), back_inserter(v));
	
	for(vector<int>::const_iterator x = u.begin(), y = v.begin(); x != u.end(); ++x, ++y)
	{
		cout << *x << ' ' << *y << endl;
	}
}

#include <numeric>

string concatenate(const vector<string>& strings)
{
	return accumulate(strings.begin(), strings.end(), string(""));
}

#pragma mark - Chapitre 7

#include <map>

map <string, vector<int> > map_words_in_lines (istream& input, vector<string> find_words(const string&) = split )
{
	string line;
	map <string, vector<int> > output;
	int currentLine = 0;
	
	while(getline(input, line))
	{
		++currentLine;
		
		vector<string> words = find_words(line);
		vector<string>::iterator iterator = words.begin();
		
		while(iterator != words.end())
		{
			map<string, vector<int> >::iterator found = output.find(*iterator);
			if(found != output.end())
			{
				vector<int> lines = found->second;
				if(find(lines.begin(), lines.end(), currentLine) == lines.end())
				{
					output[*iterator].push_back(currentLine);
				}
			}
			else
			{
				output[*iterator].push_back(currentLine);
			}
			++iterator;
		}
	}
	return output;
}

void map_words()
{
	
	map<string, vector<int> > wordMapping = map_words_in_lines(cin);
	map<string, vector<int> >::iterator iterator = wordMapping.begin();
	while (iterator != wordMapping.end())
	{
		string word = iterator->first;
		vector<int> lines = iterator->second;
		vector<int>::iterator linesIterator = lines.begin();
		
		cout << "The word " << word << " appears in theses lines: " << *linesIterator;
		++linesIterator;
		
		while (linesIterator != lines.end())
		{
			cout << ", " << *linesIterator;
			++linesIterator;
		}
		cout << endl;
		
		++iterator;
	}
}

bool comparator(pair<string, int>& x, pair<string, int>& y)
{
	return x.second < y.second;
}

void count_words_using_map()
{
	string s;
	map<string, int> counter;
	
	while(cin >> s)
	{
		++counter[s];
	}
	
	vector< pair<string, int> > orderedCounter(counter.begin(), counter.end());
	sort(orderedCounter.begin(), orderedCounter.end(), comparator);
	for(vector< pair<string, int> >::const_iterator iterator = orderedCounter.begin(); iterator != orderedCounter.end(); ++iterator)
	{
		cout << "The word " << iterator->first << " has been counted " << iterator->second << " times." << endl;
	}
}

typedef vector<string> Rule;
typedef vector<Rule> RuleCollection;
typedef map <string, RuleCollection> Grammar;

Grammar append_rule(const string& line, Grammar& output)
{
	vector<string> entry = split(line);
	if(!entry.empty())
	{
		output[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
	}
	return output;
}

Grammar read_grammar(istream& input)
{
	Grammar output;
	string line;
	
	while(getline(input, line))
	{
		append_rule(line, output);
	}
	return output;
}

bool bracketed (const string& input)
{
	return (input.size() > 1 && input[0] == '<' && input[input.size() - 1] == '>');
}

int nrand(unsigned long size)
{
	//return rand() % size;
	
	if(size <= 0 || size > RAND_MAX)
	{
		throw domain_error("Argument out of range");
	}
	
	const int bucket_size = RAND_MAX / size;
	
	int output;
	do output = rand() / bucket_size;
	while(output >= size);
	
	return output;
}

void generate_auxiliary(const Grammar& grammar, const string& word, vector<string>& input)
{
	if(!bracketed(word))
	{
		input.push_back(word);
	}
	else
	{
		Grammar::const_iterator iterator = grammar.find(word);
		if(iterator == grammar.end())
		{
			throw logic_error("Empty rule");
		}
		
		const RuleCollection& collection = iterator->second;
		const Rule& rules = collection[nrand(collection.size())];
		for(Rule::const_iterator ruleIterator = rules.begin(); ruleIterator != rules.end(); ++ruleIterator)
		{
			generate_auxiliary(grammar, *ruleIterator, input);
		}
	}
}

vector<string> generate_sentence(const Grammar& grammar)
{
	vector<string> output;
	generate_auxiliary(grammar, "<sentence>", output);
	return output;
}

Grammar static_grammar()
{
	Grammar grammar;
	
	append_rule("<noun> cat", grammar);
	append_rule("<noun> dog", grammar);
	append_rule("<noun> table", grammar);
	append_rule("<noun> star", grammar);
	append_rule("<noun-phrase> <noun>", grammar);
	append_rule("<noun-phrase> <adjective> <noun-phrase>", grammar);
	append_rule("<adjective> large", grammar);
	append_rule("<adjective> brown", grammar);
	append_rule("<adjective> crazy", grammar);
	append_rule("<verb> jumps", grammar);
	append_rule("<verb> shines", grammar);
	append_rule("<verb> sits", grammar);
	append_rule("<location> on the stairs", grammar);
	append_rule("<location> under the sky", grammar);
	append_rule("<location> behind the moon", grammar);
	append_rule("<location> wherever it wants", grammar);
	append_rule("<sentence> The <noun-phrase> <verb> <location>", grammar);
				
	return grammar;
}

void sentence_generator()
{
	// vector<string> sentence = generate_sentence(read_grammar(cin));
	vector<string> sentence = generate_sentence(static_grammar());
	
	vector<string>::const_iterator iterator = sentence.begin();
	if(!sentence.empty())
	{
		cout << *iterator;
		++iterator;
	}
	while(iterator != sentence.end())
	{
		cout << " " << *iterator;
		++iterator;
	}
	cout << "." << endl;
}

#pragma mark - Chapitre 8

template <class T>
T median(vector<T> input)
{
	typedef typename vector<T>::size_type vector_size;
	vector_size size = input.size();
	
	if(size == 0)
	{
		throw domain_error("impossible to calculate median of empty vector");
	}
	
	sort(input.begin(), input.end());
	
	vector_size middle = size / 2;
	return size % 2 == 0 ? (input[middle] + input[middle - 1]) / 2 : input[middle];
}

#pragma mark - Main

int main(int argc, const char * argv[])
{	
	// TP Supinfo courses
	// start_operation();
	
	/* TP Accelerated C++
	 * Chapters 1 & 2 */
	say_greetings_to("Benjamin", 1);
	// draw_rectangle(6, 4);
	// draw_square(5);
	// draw_triangle(4);
	
	/* Chapter 3 */
	// calculate_median();
	// calculate_quartiles();
	// count_disctinct_words();
	// shortest_and_longest_word();
	
	/* Chapter 4 */
	// print_squares(1000);
	// calculate_average();
	
	/* Chapter 5 */
	// read_line_then_separe_it();
	// read_line_then_frame_it();
	// concat_two_character_frames();
	
	/* Chapter 6 */
	// back_inserter_test();
	// cout << concatenate(read_line_then_separe_it());
	
	/* Chapter 7 */
	// count_words_using_map();
	// map_words();
	// sentence_generator();
	
	cout << endl << endl << "Bye bye birdie!" << endl;
	return 0;
}
