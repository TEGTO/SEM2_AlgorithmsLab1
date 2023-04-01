#pragma once
#include <vector>
#include <sstream>
class FixedSet
{
    // min 36500, sweetspot 73000
    static const int _size = 10000000;
    int _noentry;
    std::vector<int> _set1;
    std::vector<int> _set2;
    std::vector<int> _set3;

public:
    FixedSet() : _noentry(std::numeric_limits<int>::min()), _set1(_size, _noentry), _set2(_size, _noentry), _set3(_size, _noentry) {  }

    void StringInitialize(std::string letter)
    {
        std::vector<int>numbers;
        std::string message;
        for (int i = 0; i < letter.length(); i++)
        {
            char x = letter.at(i);
            message += std::to_string(int(x));
            if (i%6==0)
            {
                numbers.push_back(std::stoll(message));
                message = "";
            }

        }
        numbers.push_back(std::stoll(message));
        Initialize(numbers);
    }
    bool StringContains(std::string letter)
    {
        std::string message;
        for (int i = 0; i < letter.length(); i++)
        {
            char x = letter.at(i);
            message += std::to_string(int(x));
            if (i % 6 == 0)
            {
                if (!Contains(std::stoll(message)))
                {
                    return false;
                }
                message = "";
            }
          
        }
       
        if (!Contains(std::stoll(message)))
        {
            return false;
        }
        return true;
    }
    void Initialize(const std::vector<int>& numbers)
    {
        for (int i = 0; i < numbers.size(); ++i)
        {
            if (!Contains(numbers[i]))
            {
                if (!add(numbers[i]))
                {
                    std::ostringstream o;
                    throw new std::exception(o.str().c_str());
                }
            }
        }
    }

    bool Contains(int number)
    {
        for (int round = 0; round < 3; ++round)
        {
            std::vector<int>& _set = (round % 3 == 0) ? _set1 : ((round % 3 == 1) ? _set2 : _set3);
            int h = hash(round + 1, number);
            if (number == _set[h])
                return true;
        }
        return false;
    }

private:
    int hash(int rounds, int number)
    {
        int withOffset = number;
        srand(withOffset);
        int h = bigRand() % _size;
        while (--rounds)
        {
            h = bigRand() % _size;
        }
        return h;
    }

    inline int bigRand()
    {
        return (rand() << 15) | rand(); 
    }

    bool add(int number)
    {
        int toInsert = number;
        for (int i = 0; i < _size; ++i)
        {
            
            int h = hash(i % 3 + 1, toInsert);
            std::vector<int>& _set = (i % 3 == 0) ? _set1 : ((i % 3 == 1) ? _set2 : _set3);
            int current = _set[h];
            if (current == _noentry)
            {
                _set[h] = toInsert;
                return true;
            }
            _set[h] = toInsert;
            toInsert = current;
        }

        return false;
    }
};