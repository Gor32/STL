#include "BinaryRelation.h"
#include <iostream>

using namespace std;
BinaryRelation::BinaryRelation(int n) :n_(n), relation_(new SetOfPairs())
{
}

BinaryRelation::BinaryRelation(const BinaryRelation & other) : n_(other.n_), relation_(new SetOfPairs())
{
	for (CIterator it1 = other.relation_->begin(); it1 != other.relation_->end(); it1++)
	{
		this->relation_->insert(make_pair(it1->first, it1->second));
	}

}

BinaryRelation & BinaryRelation::operator=(const BinaryRelation & other)
{
	this->relation_ = other.relation_  ;
	this->n_ = other.n_;
	return *this;
}

bool BinaryRelation::isReflexive() const
{

	for (int i = 1; i <= this->n_; i++)
		if (this->relation_->find(make_pair(i, i)) == this->relation_->end())
			return false;

	return true;
}

bool BinaryRelation::isSymmetric() const
{
	for (CIterator it = this->relation_->begin(); it != this->relation_->end(); it++)
	{
		if (this->relation_->find(make_pair(it->second, it->first)) == this->relation_->end())
			return false;
	}

	return true;
}

bool BinaryRelation::isAntisymmetric() const
{
	for (CIterator it = this->relation_->begin(); it != this->relation_->end(); it++)
	{
		if (this->relation_->find(make_pair(it->second, it->first)) != this->relation_->end())
			if (it->second != it->first) return false;
	}

	return true;
}

bool BinaryRelation::isTransitive() const
{
	for (CIterator it1 = this->relation_->begin(); it1 != this->relation_->end(); it1++)
	{
		for (CIterator it2 = this->relation_->begin(); it2 != this->relation_->end(); it2++)
		{
			
			if (it1->first== it2->first&&it1->second == it2->second) continue;

			if (it2->first != it1->second) continue;
			

			if (this->relation_->find(make_pair(it1->first, it2->second)) == this->relation_->end())
				return false;
		}
	}
	return true;
}

bool BinaryRelation::isEquivalence() const
{
	return isSymmetric() && isReflexive() && isTransitive();
}



bool BinaryRelation::isOrder() const
{
	return this->isReflexive() && this->isAntisymmetric()&&this->isTransitive();
}

BinaryRelation BinaryRelation::operator+(const BinaryRelation & other) const
{
	BinaryRelation result(*this);
	
	result.n_ = this->n_ > other.n_ ? this->n_ : other.n_;

	for (CIterator it1 = other.relation_->begin(); it1 != other.relation_->end(); it1++) {
		result.relation_->insert(make_pair(it1->first, it1->second));
	}

	return result;
}

BinaryRelation BinaryRelation::operator*() const
{

	BinaryRelation result(*this);
	BinaryRelation previous;

	do
	{
		previous = result;
		result = result * (*this);
		result = result + previous;

	} while (previous != result);

	return result;
}



BinaryRelation BinaryRelation::operator*(const BinaryRelation & other) const
{
	BinaryRelation result(this->n_>other.n_ ? this->n_ : other.n_);

	for (CIterator it1 = this->relation_->begin(); it1 != this->relation_->end(); it1++)
	{
		for (CIterator it2 = other.relation_->begin(); it2 != other.relation_->end(); it2++)
		{
			if (it1->second == it2->first) {
				result.relation_->insert(make_pair(it1->first, it2->second));
				
			}
		}
	}

	return result;
}



bool BinaryRelation::operator==(const BinaryRelation & other) const
{

	BinaryRelation b(other);

	for (BinaryRelation::CIterator it = this->relation_->begin(); it != this->relation_->end(); it++)
	{
		b.relation_->erase(make_pair(it->first, it->second));
	}

	return b.relation_->empty();
}

bool BinaryRelation::operator!=(const BinaryRelation & other) const
{
	return !(*this == other);
}



istream & operator>>(std::istream & input, BinaryRelation & relation)
{

	std::cout << "\t\tINPUT" << endl;
	int n;
	std::cout << "input count :: ";
	input >> n;
	for (int i = 1; i < n + 1; i++)
	{
		int first, second;
		std::cout << "input first and second " << i << ":: ";
		input >> first >> second;

		if (first > relation.n_ | second > relation.n_) cout << "first or second > n_" << endl;
		else relation.relation_->insert(make_pair(first, second));
	}

	return input;

}

ostream & operator<<(std::ostream & output, const BinaryRelation & relation)
{
	std::cout << "\t\tOUTPUT" << std::endl;

	int i = 1;
	for (BinaryRelation::CIterator it = relation.relation_->begin(); it != relation.relation_->end(); it++, i++)
	{
		output << "output first and second " << i << ":: " << it->first << " " << it->second << endl;
	}

	return output;
}
