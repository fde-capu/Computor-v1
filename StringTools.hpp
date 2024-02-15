#ifndef STRINGTOOLS_HPP
# define STRINGTOOLS_HPP

# include <iostream>
# include <sstream>
# include <vector>
# include <cstdio>
# include <string.h>
# include "defines.hpp"
# include <stdexcept>

# define VERBOSE_ELEVATION 1
# define VERBOSE_LINE_LIMIT  60
# define verbose(X) if (VERBOSE >= X + VERBOSE_ELEVATION) std::cout
# define SHORT(X) X.substr(0, VERBOSE_LINE_LIMIT ) << " (" << X.length() << ")"

# define DEBUG_BREAK(X) static int DEB = X; if (DEB-- <= 0) throw std::runtime_error("Debug break!");

# define ST_SOFT_TRIM " \t\n\r"
# define ST_HARD_TRIM " \t"
# define ST_QUOTE_SET "\"'`"
# define ST_COMMENT_INLINE "#"
# define ST_DEFAULT_QUOTE "'"
# define ST_WORD_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789-"
# define ST_FILENAME_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./-_"
# define ST_URI_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./-_:"
# define ST_BOOL_WORDS "0 1 off on false true"
# define ST_DEFAULT_SPLIT " "

# define ST_ID "(StringTools) "
# define ST_ERR_UNMATCHED_BRACKETS ST_ID " Unmatched bracket."

bool		isWordContained(const std::string&, const std::string&);
void		remove_dup_char(std::string&, const char);
void		remove_rep_char(std::string&, const char);
std::string	to_lower(std::string);
std::string	to_upper(std::string);
bool		is_equal_insensitive(const std::string, const std::string);
std::string trim(std::string&);
std::string& trim(std::string& str, std::string set);
void		soft_trim(std::string&);
void		soft_trim(std::string&, std::string);
void 		hard_trim(std::string&);
std::string	hard_trim(const std::string&);
void		hard_trim(std::string&, std::string);
std::string	dual_trim(std::string&, std::string);
void		remove_all(std::string&, std::string);
std::string& substitute_all(std::string&, std::string, std::string);
std::string& substitute_unloop(std::string& dst, std::string before, std::string after);
std::string	substitute_super(std::string&, std::string, std::string);
void		erase_boundaries(std::string&, std::string);
void		erase_boundaries(std::string&, std::string, std::string);
size_t		find_closing_bracket(std::string);
void		remove_comments(std::string&);
std::string	remove_quotes(std::string&);
std::string	remove_quotes(const std::string&);
std::string	escape_char(const std::string, std::string);
bool		isNumber(const std::string&);
bool		isNumberChar(const char& c);
bool		isAllNumber(std::vector<std::string>);
bool		isAllNumber(std::string);
bool		isDigit(char);
bool		isWord(const std::string);
bool		isWordInWordSet(std::string, std::vector<std::string>);
bool		isBoolStr(std::string);
std::string	itos(int);
std::string	apply_quotes(std::string);
std::string	apply_quotes(std::string, std::string);
std::vector<std::string> split(const std::string str, const std::string sep = ST_DEFAULT_SPLIT);
std::vector<std::string> split_trim(const std::string, const std::string);
std::vector<std::string> splitOutsideQuotes(std::string);
std::string	itoa(int);
bool		isFileName(std::string);
bool		is_size_t(std::string);
bool		is_int(std::string);
bool		isUri(std::string);
bool		isAllInSet(std::string, std::string);
std::string	nth_word(std::string, int);
size_t		word_count(std::string);
std::string	word_from(const std::string&, size_t);
size_t		find_outside_quotes_set(std::string& str, std::string set, size_t u_start = 0);
size_t		find_outside_quotes(std::string& str, std::string needle, size_t u_start = 0);
std::pair<size_t, size_t> find_char_sequence(const std::string& src, char x, size_t = 0);
std::string	consume_until(std::string& src, const std::string delim_str);
std::string	consume_delims(std::string& src, const std::string delim_set);
std::string	stoa(size_t i);
std::string	get_file_extension(const std::string fpath);
std::string	remove_filename_from_path(const std::string fpath);
bool		not_in_word_set(char x);
std::string	query_for(std::string query, std::string& src);
bool		isInSet(const char& test_char, std::string set);
bool		startsWith(const std::string& full, const std::string& begining);
std::string	consume_bytes(std::string& src, size_t bytes);
void		just_consume_until(std::string& src, const std::string delim_str);
std::string	get_after_until_line(const std::string& src, const std::string phrase);
std::string	get_after_first(const std::string& src, const std::string phrase);
std::string	get_before_first(const std::string& src, const std::string phrase);
size_t		strhex2size_t(const std::string src);
std::vector<char*> vecstr2veccharp(const std::vector<std::string>& argv);
std::string	dtoa(double, size_t precision = 0);
std::string remove_x_ponential(const std::string&);

template <typename T>
std::ostream & operator << (std::ostream & os, const std::vector<T> & vec)
{
	size_t i = -1;

	os << "[ ";
	while (++i < vec.size())
    {
        os << vec[i];
		if (i + 1 < vec.size())
			std::cout << " , ";
    }
	os << " ]";
    return os;
}

#endif
