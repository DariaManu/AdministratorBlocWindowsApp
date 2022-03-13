#pragma once
#include "RepoLocatari.h"
#include "Locatar.h"

class FakeRepository : public RepoLocatari
{
public:

	void adauga_locatar(const Locatar& locatar) override;

};

