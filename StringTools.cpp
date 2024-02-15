#include "StringTools.hpp"
#include <iostream>

std::string st_word_set(ST_WORD_SET);
std::string _quote_set(ST_QUOTE_SET);
std::string _hard_trim_set(ST_HARD_TRIM);
std::string _soft_trim_set(ST_SOFT_TRIM);

std::string hard_trim(const std::string &dst)
{
	std::string out(dst);
	hard_trim(out);

	return out;
}

void hard_trim(std::string &dst)
{ hard_trim(dst, _hard_trim_set); }

void hard_trim(std::string& dst, std::string set)
{
	for (std::string::iterator i = set.begin(); *i; i++)
	{
		std::string trimmed = std::string(i, i + 1) + std::string(i, i + 1);
		substitute_super(dst, trimmed, std::string(i, i + 1));
	}
	soft_trim(dst);
}

void soft_trim(std::string& dst, std::string set)
{
	bool pass = false;

	while (!pass)
	{
		pass = true;
		for (std::string::iterator i = set.begin(); *i; i++)
		{
			if (*dst.begin() == *i)
			{
				dst = dst.substr(1);
				pass = false;
			}
			if (*(dst.end() - 1) == *i)
			{
				dst = dst.substr(0, dst.size() - 1);
				pass = false;
			}
		}
	}
}

void erase_boundaries(std::string &dst, std::string center)
{
	for (std::string::iterator i = center.begin(); *i; i++)
		erase_boundaries(dst, std::string(i, i + 1), _soft_trim_set);
}

void erase_boundaries(std::string &dst, std::string center, std::string trim_set)
{
	for (std::string::iterator i = trim_set.begin(); *i; i++)
	{
		std::string nlpv = std::string(i, i + 1) + center;
		std::string nlnx = center + std::string(i, i + 1);
		substitute_super(dst, nlpv, center);
		substitute_super(dst, nlnx, center);
	}
}

void soft_trim(std::string& dst)
{ soft_trim(dst, _soft_trim_set); }

std::string dual_trim(std::string& dst, std::string set)
{
	while (*dst.begin() == *set.begin() && *(dst.end() - 1) == *(set.end() - 1))
		dst = dst.substr(1, dst.size() - 2);
	return dst;
}

void remove_comments(std::string& dst)
{
	std::string line;
	std::string new_p = "";
	std::istringstream ptois(dst);
	std::string new_line;

	while (std::getline(ptois, line))
	{
		new_line = line.substr(0, line.find(ST_COMMENT_INLINE)) + "\n";
		if (new_line != "\n")
			new_p += new_line;
	}
	dst = new_p;
}

void remove_all(std::string& dst, std::string to_remove)
{ substitute_super(dst, to_remove, ""); }

std::string itos(int i)
{
	std::ostringstream s;

	s << i;
	return std::string(s.str());
}

std::string substitute_super(std::string& dst, std::string before, std::string after)
{
	int V(30);
	bool pass = false;
	while (!pass)
	{
		pass = true;
		size_t pos = find_outside_quotes(dst, before);
		size_t scap_t = find_outside_quotes(dst, std::string("\\" + before));
		verbose(V) << "(substitute_super) pos scap_t " << pos << " " << scap_t << std::endl;
		if
		(
			(pos != std::string::npos)
			&&
			(
				(pos != scap_t + 1)
				||
				(pos == 0 && scap_t == std::string::npos)
			)
		)
		{
			pass = false;
			verbose(V) << "(substitute_super) replacing " << pos << std::endl;
			dst.replace(pos, before.length(), after);
		}
	}
	return dst;
}

std::string& substitute_unloop(std::string& dst, std::string before, std::string after)
{
	std::string out;
	size_t i = -1;

	while (++i < dst.length())
	{
		if (dst.substr(i).find(before) == 0)
		{
			out += after;
			i += before.length() - 1;
		}
		else
		{
			out += dst.at(i);
		}
	}

	dst = out;
	return dst;
}

std::string& substitute_all(std::string& dst, std::string before, std::string after)
{
	bool pass = false;
	size_t lastp = 0;

	while (!pass)
	{
		pass = true;
		size_t pos = find_outside_quotes(dst, before);
		size_t scap_t = find_outside_quotes(dst, std::string("\\" + before));
		if (pos != std::string::npos && \
			(pos == 0 || (pos != scap_t + 1 && pos > lastp)))
		{
			pass = false;
			lastp = pos;
			dst.replace(pos, before.length(), after);
		}
	}
	return dst;
}

std::string apply_quotes(std::string str)
{ return apply_quotes(str, ST_DEFAULT_QUOTE); }

std::string apply_quotes(std::string str, std::string quote)
{ return std::string(quote + escape_char(str, quote) + quote); }

size_t find_outside_quotes(std::string& str, std::string needle, size_t u_start)
{
	int V(30);
	std::string q("");
	std::string::iterator e;
	std::string::iterator n;
	size_t n_find;

	verbose(V) << "(find_outside_quotes) >" << needle << "< @ " << SHORT(str) << std::endl;
	n_find = str.find(needle, u_start);
	if (n_find == std::string::npos)
		return std::string::npos;
	std::string::iterator s = str.begin() + n_find;
	while (*s)
	{
		if (*s == '\\')
			s += 2;
		if (!*s)
			break ;
		for(std::string::const_iterator i = _quote_set.begin(); *i; i++)
		{
			if (*i == *s)
			{
				if (*(q.end() - 1) == *i)
					q = q.substr(0, q.length() - 1);
				else if (q.empty())
					q += *i;
				break ;
			}
			else
			{
				if (q.length())
					continue ;
				e = s;
				n = needle.begin();
				while (*e && *n && *e == *n)
				{
					e++;
					n++;
					if (!*e && *n)
					{
						return std::string::npos;
					}
					if (!*n)
					{
						verbose(V) << "(find_outside_quotes) found @" << (s - str.begin()) << std::endl;
						return s - str.begin();
					}
				}
			}
		}
		s++;
	}
	return std::string::npos;
}

size_t find_outside_quotes_set(std::string& str, std::string set, size_t u_start)
{
	size_t out = std::string::npos;

	for (std::string::iterator i = set.begin(); *i; i++)
	{
		size_t first = find_outside_quotes(str, std::string(i, i + 1), u_start);
		if (first < out)
			out = first;
	}
	return out;
}

size_t find_closing_bracket(std::string ops)
{
	std::string stack("");
	size_t pos = 0;

	while (ops[pos])
	{
		if (ops[pos] == '{')
			stack += "{";
		if (ops[pos] == '}')
		{
			if (stack == "")
				return pos;
			stack = stack.substr(0, stack.size() - 1);
		}
		pos++;
	}
	if (!ops[pos])
	{
		return std::string::npos;
	}
	return pos;
}

std::string escape_char(const std::string dst, std::string esc)
{
	std::string out(dst);

	substitute_all(out, esc, std::string("\\" + esc));
	return out;
}

std::string remove_quotes(const std::string& dst)
{
	std::string out = dst;

	remove_quotes(*const_cast<std::string*>(&dst));
	return dst;
}

std::string remove_quotes(std::string& dst)
{
	if (find_outside_quotes(dst, " ") != std::string::npos)
		return dst;
	std::string out(dst);
	std::string::iterator f = dst.begin();
	std::string::iterator l = dst.end() - 1;
	std::string first(f, f + 1);
	std::string last(l, l + 1);
	if (first == last && (first == "\"" || first == "'"))
		out = std::string(f + 1, l);
	dst = out;
	return out;
}

bool isDigit(char d)
{ return d >= '0' && d <= '9'; }

bool isWord(const std::string w)
{ return isAllInSet(w, ST_WORD_SET); }

bool isWordContained(const std::string& word, const std::string& big_string)
{ return isWordInWordSet(word, split(big_string, " ")); }

bool isWordInWordSet(std::string w, std::vector<std::string> vstr)
{
	for (size_t i = 0; i < vstr.size(); i++)
	{
		if (vstr[i] == w)
			return true;
	}
	return false;
}

std::vector<std::string> split(const std::string str, const std::string sep)
{
	std::vector<std::string> out;
	std::string crop = str;
	size_t mark;

	mark = find_outside_quotes(crop, sep);
	while (mark != std::string::npos)
	{
		out.push_back(crop.substr(0, mark));
		crop = crop.substr(mark + sep.length());
		mark = find_outside_quotes(crop, sep);
	}
	out.push_back(crop);
	return out;
}

std::vector<std::string> split_trim(const std::string str, const std::string sep)
{
	std::vector<std::string> out = split(str, sep);
	for (size_t i = 0; i < out.size(); i++)
		trim(out[i]);
	return out;
}

std::vector<std::string> splitOutsideQuotes(const std::string vecstr)
{
	std::vector<std::string> out;
	std::string spl = remove_quotes(hard_trim(vecstr));
	size_t pos = find_outside_quotes(spl, " ");

	if (pos == std::string::npos)
	{
		out.push_back(remove_quotes(spl));
		return out;
	}
	size_t pre = 0;
	while (pos != std::string::npos)
	{
		out.push_back(remove_quotes(spl.substr(pre, pos)));
		spl = spl.substr(pos + 1);
		pos = find_outside_quotes(spl, " ");
	}
	out.push_back(remove_quotes(spl));
	return out;
}

bool isAllNumber(std::string ustr)
{ return isNumber(ustr); }

bool isAllNumber(std::vector<std::string> vecstring)
{
	for (size_t i = 0; i < vecstring.size(); i++)
		if (!isNumber(vecstring[i]))
			return false;
	return true;
}

bool isNumberChar(const char& c)
{
	return isDigit(c) || isAllInSet(std::string(1, c), "+-.");
}

bool isNumber(const std::string& u_str)
{
	std::string str(u_str);
	bool dot = false;

	soft_trim(str);
	remove_quotes(str);
	for (size_t i = 0; i < str.size(); i++)
	{
		if (i == 0 && !isNumberChar(str[i]))
			return false;
		if (i == 0 && isNumberChar(str[i]))
			continue ;
		if (str[i] == '.')
		{
			if (dot)
				return false;
			dot = true;
			continue ;
		}
		if (!isDigit(str[i]))
			return false;
	}
	return true;
}

std::string itoa(int i)
{
	std::ostringstream ss;

	ss << i;
	return ss.str();
}

std::string stoa(size_t i)
{
	std::stringstream ss;

	ss << i;
	return ss.str();
}

bool is_int(std::string isi)
{
	// Currently accepting arbitrarly large overflewd string input.
	int i_test = 0;

	if (isAllNumber(isi) && 1 == std::sscanf(isi.c_str(), "%i", &i_test))
		return true;
	return false;
}

bool is_size_t(std::string sts)
{
	// Currently accepting arbitrarly large overflewd string input.
	size_t st_test = 0;

	if (isAllNumber(sts) && 1 == std::sscanf(sts.c_str(), "%zu", &st_test))
		return true;
	return false;
}

std::string get_file_extension(const std::string fpath)
{
	std::vector<std::string> e = split(fpath, ".");
	if (e.size() <= 1)
		return "";
	return "." + e[e.size() - 1];
}

bool isFileName(std::string fn)
{ return isAllInSet(fn, ST_FILENAME_SET); }

std::string remove_filename_from_path(const std::string fpath)
{
	std::vector<std::string> u_path = split(fpath, "/");
	std::string bpath("");
	for (size_t i = 0; i < u_path.size() - 1; i++)
		bpath += u_path[i] + "/";
	return bpath;
}

bool isUri(std::string fn)
{ return isAllInSet(fn, ST_URI_SET); }

bool isAllInSet(std::string str, std::string set)
{
	size_t pass;

	for (size_t i = 0; i < str.size(); i++)
	{
		for (pass = 0; pass < set.size(); pass++)
		{
			if (str[i] == set[pass])
				break ;
		}
		if (pass >= set.size())
			return false;
	}
	return true;
}

bool not_in_word_set(char x)
{ return st_word_set.find(x) != std::string::npos; }

std::string word_from(const std::string& phrase, size_t pos)
{
	std::string word;

	while(not_in_word_set(phrase.at(pos)))
		word += phrase.at(pos++);
	return word;
}

std::string nth_word(std::string str, int n)
{
	int wc = word_count(str);

	if (n > wc)
		return "";
	while (--n >= 1)
	{
		str = str.substr(find_outside_quotes_set(str, " \n") + 1);
	}
	if (word_count(str) != 1)
		str = str.substr(0, find_outside_quotes_set(str, " \n"));
	return str;
}

size_t word_count(std::string str)
{
	int out = str.length() ? 1 : 0;

	while (find_outside_quotes_set(str, " \n") != std::string::npos && ++out)
		str = str.substr(find_outside_quotes_set(str, " \n") + 1);
	return out;
}

bool is_equal_insensitive(const std::string a, const std::string b)
{ return to_lower(a) == to_lower(b); }

std::string to_lower(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);
	return str;
}

std::string to_upper(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
	return str;
}

void remove_dup_char(std::string& dst, const char c)
{
	std::string before(2, c);
	std::string after(1, c);
	substitute_all(dst, before, after);
}

void remove_rep_char(std::string& dst, const char c)
{
	std::string before(2, c);
	std::string after(1, c);
	substitute_super(dst, before, after);
}

bool isWord(const std::string& str, size_t pos)
{ return pos < str.length() && !not_in_word_set(str.at(pos)); }

std::string query_for(std::string query, std::string& src)
{
	int V(4);
	size_t start = src.find(query);
	size_t end;
	std::string tmp("");

	verbose(V) << "(query_for) " << query << std::endl;
	if (start == std::string::npos)
		return "";
	while (start < src.length() && !isWord(src, start++)) ;
	if (start == std::string::npos)
		return "";
	end = find_outside_quotes_set(src, ";\r\n", start);
	if (end != std::string::npos)
		tmp = src.substr(start, end - start);
	return trim(tmp, " \"\'");
}

std::string trim(std::string& dst)
{
	soft_trim(dst);
	return dst;
}


bool isInSet(const char& test_char, std::string set)
{
	size_t h = 0;

	while (h < set.length())
	{
		if (set.at(h) == test_char)
			return true;
		h++;
	}
	return false;
}

bool startsWith(const std::string& full, const std::string& begining)
{ return full.find(begining) == 0; }

std::string& trim(std::string& str, std::string set)
{
	size_t start(0);
	size_t end(str.length() - 1);

	while (start < str.length() && isInSet(str.at(start), set)) start++;
	while (str.length() && isInSet(str.at(end), set)) end--;
	if (start != 0 || end != str.length() - 1)
		str = str.substr(start, end - start + 1);
	return str;
}

void just_consume_bytes(std::string& src, size_t bytes)
{
	src.erase(0, bytes);
}

std::string consume_bytes(std::string& src, size_t bytes)
{
	std::string ret;

	if (bytes >= src.length())
	{
		ret = src;
		src = "";
		return ret;
	}
	ret = src.substr(0, bytes);
	src.erase(0, bytes);
	return ret;
}

void just_consume_until(std::string& src, const std::string delim_str)
{
	size_t h(src.find(delim_str));

	if (h == std::string::npos)
	{
		src = "";
		return;
	}
	src.erase(0, h + delim_str.length());
	return;
}

std::string consume_until(std::string& src, const std::string delim_str)
{
	std::string ret;

	size_t h(src.find(delim_str));
	if (h == std::string::npos)
	{
		ret = src;
		src = "";
		return ret;
	}
	ret = src.substr(0, h);
	src.erase(0, h + delim_str.length());
	return ret;
}

std::string consume_delims(std::string& src, const std::string delim_set)
{
	size_t h(0);
	std::string ret;

	while (src.length() && h < src.length() - 1 && !isInSet(src.at(h), delim_set))
		h++;
	if (h >= src.length() - 1)
	{
		ret = src;
		src = "";
		return ret;
	}
	ret = src.substr(0, h);
	while (src.length() && h < src.length() - 1 && isInSet(src.at(h), delim_set))
		h++;
	src.erase(0, h);
	return ret;
}

std::string get_after_until_line(const std::string& src, const std::string phrase)
{
	size_t h(src.find(phrase));

	if (h == std::string::npos)
		return "";
	size_t nl(src.find("\n", h));
	size_t rl(src.find("\r", h));
	size_t b = nl < rl ? nl : rl;
	return src.substr(h + phrase.length(), b - (h + phrase.length()));
}

std::string get_after_first(const std::string& src, const std::string phrase)
{
	size_t h(src.find(phrase));

	if (h == std::string::npos)
		return "";
	return src.substr(h + phrase.length());
}

std::string get_before_first(const std::string& src, const std::string phrase)
{
	size_t h(src.find(phrase));

	if (h == std::string::npos)
		return src;
	return src.substr(0, h);
}

size_t strhex2size_t(const std::string src)
{
	return static_cast<size_t>(strtoul(src.c_str(), NULL, 16));
}

std::vector<char*> vecstr2veccharp(const std::vector<std::string>& argv)
{
	std::vector<char*> vec_cp;
	vec_cp.reserve(argv.size() + 1);
	for (size_t i = 0; i < argv.size(); i++)
		vec_cp.push_back(strdup(argv[i].c_str()));
	vec_cp.push_back(NULL);
	return vec_cp;
}

std::pair<size_t, size_t> find_char_sequence(const std::string& src, char x, size_t start_position)
{
	int V(3);
	size_t i = start_position - 1;
	size_t start = std::string::npos;
	size_t count = 0;

	while (++i < src.length())
	{
		if (src.at(i) == x)
		{
			verbose(V) << "(frcdo) " << src << ": " << i << ":: " << src.at(i) << " == " << x << std::endl;
			if (!count)
				start = i;
			count++;
			verbose(V) << "(frcdo) " << src << ": " << i << ":: start: " << start << ", count: " << count << std::endl;
		}
		else if (count >= 1)
			break ;
		else if (count)
			count = 0;
	}
	if (count >= 1)
	{
		verbose(V) << "(frcdo) " << src << " Returning start: " << start << ", count: " << count << std::endl;
		return std::pair<size_t, size_t>{start, count};
	}
	verbose(V) << "(frcdo) Did not find, returning std::string::npos!" << std::endl;
	return std::pair<size_t, size_t>{std::string::npos, std::string::npos};
}

std::string dtoa(double n, size_t precision)
{
	std::string str{std::to_string (n)};
	int offset{1};

	if (str.find_last_not_of('0') == str.find('.')) {
		offset = 0;
	}
	str.erase(str.find_last_not_of('0') \
		+ offset, std::string::npos);
	if (!precision)
		return str;

	size_t i = 0;
	size_t count = 0;
	while (i < str.length())
	{
		if (count)
			count++;
		if (str[i] == '.')
			count = 1;
		i++;
	}
	while (count < 6)
	{
		str += "0";
		count++;
	}
	return str;
}

std::string remove_x_ponential(const std::string& e)
{
	bool reading = true;
	std::string out;

	for (size_t i = 0; i < e.length(); i++)
	{
		if (isInSet(e.at(i), "x"))
		{
			reading = false;
			continue;
		}
		if (isInSet(e.at(i), "*/-+"))
		{
			reading = true;
		}
		if (reading)
			out += e.at(i);
	}
	substitute_super(out, "**", "*");
	substitute_super(out, "//", "/");
	out = std::regex_replace(out, std::regex("\\*$"), "");
	return out;
}

std::vector<std::string> splitNumbers(const std::string& e)
{
	std::vector<std::string> tokens;
	std::regex re("([-|+]?\\d+(?:\\.\\d+)?|\\D)");
	for (std::sregex_iterator it(e.begin(), e.end(), re), end; it != end; ++it) {
		tokens.push_back((*it).str());
	}
	return tokens;
}
