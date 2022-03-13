#pragma once
#include <memory>

template <typename ElementType>
class Iterator;

template <typename ElementType>
class VectorDinamic
{
private:
	//ElementType* elemente;
	std::unique_ptr<ElementType[]> elemente;
	int dimensiune;
	int capacitate;

	void redimensionare();

public:
	VectorDinamic();

	//~VectorDinamic();
	~VectorDinamic() = default;

	VectorDinamic(const VectorDinamic &altVector);

	VectorDinamic& operator=(const VectorDinamic &altVector);

	void adauga_final(const ElementType &element);

	void sterge_pozitie(int pozitie);

	void interschimba_elemente(int pozitie1, int pozitie2);

	const ElementType& get_element(int pozitie) const noexcept;
	
	int get_dimensiune() const noexcept;

	friend class Iterator<ElementType>;
	Iterator<ElementType> begin() noexcept;
	Iterator<ElementType> end() noexcept;
};

template <typename ElementType>
VectorDinamic<ElementType>::VectorDinamic()
{
	//this->elemente = new ElementType[2];
	this->elemente = std::make_unique<ElementType[]>(2);
	this->dimensiune = 0;
	this->capacitate = 2;
}

/*template <typename ElementType>
VectorDinamic<ElementType>::~VectorDinamic()
{
	delete[] this->elemente;
}*/

template <typename ElementType>
VectorDinamic<ElementType>::VectorDinamic(const VectorDinamic &altVector)
{
	this->capacitate = altVector.capacitate;
	this->dimensiune = altVector.dimensiune;
	//this->elemente = new ElementType[altVector.capacitate];
	this->elemente = std::make_unique<ElementType[]>(altVector.capacitate);
	for (int i = 0; i < altVector.dimensiune; i++)
		this->elemente[i] = altVector.elemente[i];
}

template <typename ElementType>
VectorDinamic<ElementType>& VectorDinamic<ElementType>::operator=(const VectorDinamic<ElementType> &altVector)
{
	if (this == &altVector)
		return *this;

	//delete[] this->elemente;
	//this->elemente = new ElementType[altVector.capacitate];
	this->elemente = std::make_unique<ElementType[]>(altVector.capacitate);
	for (int i = 0; i < altVector.dimensiune; i++)
		this->elemente[i] = altVector.elemente[i];
	this->capacitate = altVector.capacitate;
	this->dimensiune = altVector.dimensiune;
	return *this;
}

template <typename ElementType>
void VectorDinamic<ElementType>::redimensionare()
{
	//ElementType* elemente_noi = new ElementType[2 * capacitate];
	this->capacitate = capacitate * 2;
	auto elemente_noi = std::make_unique<ElementType[]>(capacitate);
	for (int i = 0; i < dimensiune; i++)
		elemente_noi[i] = elemente[i];
	//delete[] this->elemente;
	//this->elemente = elemente_noi;
	elemente.reset();
	std::swap(elemente, elemente_noi);
}

template <typename ElementType>
void VectorDinamic<ElementType>::adauga_final(const ElementType &element)
{
	if (dimensiune == capacitate)
		redimensionare();
	elemente[dimensiune] = element;
	dimensiune++;
}

template <typename ElementType>
void VectorDinamic<ElementType>::sterge_pozitie(int pozitie)
{
	//ElementType* elemente_noi = new ElementType[capacitate];
	auto elemente_noi = std::make_unique<ElementType[]>(capacitate);
	int j = 0;
	for(int i=0; i<dimensiune; i++)
		if (i != pozitie)
		{
			elemente_noi[j] = elemente[i];
			j++;
		}
	//delete[] this->elemente;
	//this->elemente = elemente_noi;
	elemente.reset();
	std::swap(elemente, elemente_noi);
	dimensiune--;
}

template <typename ElementType>
void VectorDinamic<ElementType>::interschimba_elemente(int pozitie1, int pozitie2)
{
	ElementType element_auxiliar;
	element_auxiliar = elemente[pozitie1];
	elemente[pozitie1] = elemente[pozitie2];
	elemente[pozitie2] = element_auxiliar;
}

template <typename ElementType>
const ElementType& VectorDinamic<ElementType>::get_element(int pozitie) const noexcept
{
	return elemente[pozitie];
}

template <typename ElementType>
int VectorDinamic<ElementType>::get_dimensiune() const noexcept
{
	return dimensiune;
}

template <typename ElementType>
Iterator<ElementType> VectorDinamic<ElementType>::begin() noexcept
{
	return Iterator<ElementType>(*this);
}

template <typename ElementType>
Iterator<ElementType> VectorDinamic<ElementType>::end() noexcept
{
	return Iterator<ElementType>(*this, dimensiune);
}

#/////////ITERATOR////////////////
template <typename ElementType>
class Iterator
{
private:
	const VectorDinamic<ElementType> &v;
	int pozitie = 0;

public:
	Iterator(const VectorDinamic<ElementType> &vector) noexcept;
	Iterator(const VectorDinamic<ElementType> &vector, int pozitie) noexcept;

	bool valid() const noexcept;
	ElementType& element() const noexcept;
	void urmator() noexcept;

	ElementType& operator*() noexcept;
	Iterator& operator++() noexcept;
	bool operator==(const Iterator &altVector) noexcept;
	bool operator!=(const Iterator &altVector) noexcept;
};

template <typename ElementType>
Iterator<ElementType>::Iterator(const VectorDinamic<ElementType> &vector) noexcept : v{ vector } {

}

template <typename ElementType>
Iterator<ElementType>::Iterator(const VectorDinamic<ElementType> &vector, int pozitie) noexcept : v{ vector }, pozitie{ pozitie }{

}

template <typename ElementType>
bool Iterator<ElementType>::valid() const noexcept
{
	return this->pozitie < v.dimensiune;
}

template <typename ElementType>
ElementType& Iterator<ElementType>::element() const noexcept
{
	return v.elemente[this->pozitie];
}

template <typename ElementType>
void Iterator<ElementType>::urmator() noexcept
{
	this->pozitie++;
}

template <typename ElementType>
ElementType& Iterator<ElementType>::operator*() noexcept
{
	return element();
}

template <typename ElementType>
Iterator<ElementType>& Iterator<ElementType>::operator++() noexcept
{
	urmator();
	return *this;
}

template <typename ElementType>
bool Iterator<ElementType>::operator==(const Iterator<ElementType> &altVector) noexcept
{
	return this->pozitie == altVector.pozitie;
}

template <typename ElementType>
bool Iterator<ElementType>::operator!=(const Iterator<ElementType> &altVector) noexcept
{
	return !(*this == altVector);
}