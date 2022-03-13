#pragma once
#include "RepoLocatari.h"
#include "Locatar.h"
#include "RepoAbstract.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo()=default;
};

//////////////////////////////////////////////
class UndoAdauga : public ActiuneUndo
{
private:
	RepoAbstract &repo_locatari;
	Locatar locatar;

public:
	UndoAdauga(RepoAbstract &repo_locatari, const Locatar &locatar) : repo_locatari{ repo_locatari }, locatar{ locatar }{

	};

	void doUndo() override;

};

///////////////////////////////////////////////
class UndoSterge : public ActiuneUndo
{
private:
	RepoAbstract&repo_locatari;
	Locatar locatar;

public:
	UndoSterge(RepoAbstract&repo_locatari, const Locatar &locatar) noexcept : repo_locatari{ repo_locatari }, locatar{ locatar }{

	};

	void doUndo() override;
};

//////////////////////////////////////////////
class UndoModificaNume : public ActiuneUndo
{
private:
	RepoAbstract&repo_locatari;
	Locatar locatar;

public:
	UndoModificaNume(RepoAbstract&repo_locatari, const Locatar &locatar) noexcept : repo_locatari{ repo_locatari }, locatar{ locatar }{

	};

	void doUndo() override;
};

////////////////////////////////////////////////
class UndoModificaSuprafata : public ActiuneUndo
{
private:
	RepoAbstract&repo_locatari;
	Locatar locatar;

public:
	UndoModificaSuprafata(RepoAbstract&repo_locatari, const Locatar &locatar) noexcept : repo_locatari{ repo_locatari }, locatar{ locatar }{

	};

	void doUndo() override;
};

///////////////////////////////////////////////
class UndoModificaTip : public ActiuneUndo
{
private:
	RepoAbstract&repo_locatari;
	Locatar locatar;

public:
	UndoModificaTip(RepoAbstract&repo_locatari, const Locatar &locatar) noexcept : repo_locatari{ repo_locatari }, locatar{ locatar }{

	};

	void doUndo() override;
};

