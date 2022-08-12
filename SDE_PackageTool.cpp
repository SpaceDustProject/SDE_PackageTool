#include "SDE_PackageTool.h"

#include <new>
#include <list>

class SDE_PackageTool::LuaEnumRegList::Impl
{
public:
	std::list<LuaEnumReg> m_listLuaEnumReg;

public:
	Impl(const std::initializer_list<LuaEnumReg>& ilLuaEnumReg) :
		m_listLuaEnumReg(ilLuaEnumReg) {}
};

size_t SDE_PackageTool::LuaEnumRegList::GetSize() const
{
	return m_pImpl->m_listLuaEnumReg.size();
}

void SDE_PackageTool::LuaEnumRegList::Foreach(std::function<void(const SDE_PackageTool::LuaEnumReg&)> funcCalled) const
{
	for (std::list<LuaEnumReg>::iterator iter = m_pImpl->m_listLuaEnumReg.begin();
		iter != m_pImpl->m_listLuaEnumReg.end(); iter++)
	{
		funcCalled(*iter);
	}
}

SDE_PackageTool::LuaEnumRegList::LuaEnumRegList(const std::initializer_list<LuaEnumReg>& ilLuaEnumReg)
{
	m_pImpl = new Impl(ilLuaEnumReg);
}

SDE_PackageTool::LuaEnumRegList::~LuaEnumRegList()
{
	delete m_pImpl;
}

class SDE_PackageTool::LuaFuncRegList::Impl
{
public:
	std::list<LuaFuncReg> m_listLuaFuncReg;

public:
	Impl(const std::initializer_list<LuaFuncReg>& ilLuaFuncReg) :
		m_listLuaFuncReg(ilLuaFuncReg) {}
};

size_t SDE_PackageTool::LuaFuncRegList::GetSize() const
{
	return m_pImpl->m_listLuaFuncReg.size();
}

void SDE_PackageTool::LuaFuncRegList::Foreach(std::function<void(const SDE_PackageTool::LuaFuncReg&)> funcCalled) const
{
	for (std::list<LuaFuncReg>::iterator iter = m_pImpl->m_listLuaFuncReg.begin();
		iter != m_pImpl->m_listLuaFuncReg.end(); iter++)
	{
		funcCalled(*iter);
	}
}

SDE_PackageTool::LuaFuncRegList::LuaFuncRegList(const std::initializer_list<LuaFuncReg>& ilLuaFuncReg)
{
	m_pImpl = new Impl(ilLuaFuncReg);
}

SDE_PackageTool::LuaFuncRegList::~LuaFuncRegList()
{
	delete m_pImpl;
}

class SDE_PackageTool::LuaMetatableRegList::Impl
{
public:
	std::list<LuaMetatableReg> m_listMetatableReg;

public:
	Impl(const std::initializer_list<LuaMetatableReg>& ilMetatableReg) :
		m_listMetatableReg(ilMetatableReg) {}
};

size_t SDE_PackageTool::LuaMetatableRegList::GetSize() const
{
	return m_pImpl->m_listMetatableReg.size();
}

void SDE_PackageTool::LuaMetatableRegList::Foreach(std::function<void(const LuaMetatableReg&)> funcCalled) const
{
	for (std::list<LuaMetatableReg>::iterator iter = m_pImpl->m_listMetatableReg.begin();
		iter != m_pImpl->m_listMetatableReg.end(); iter++)
	{
		funcCalled(*iter);
	}
}

SDE_PackageTool::LuaMetatableRegList::LuaMetatableRegList(const std::initializer_list<LuaMetatableReg>& ilMetatableReg)
{
	m_pImpl = new Impl(ilMetatableReg);
}

SDE_PackageTool::LuaMetatableRegList::~LuaMetatableRegList()
{
	delete m_pImpl;
}

class SDE_PackageTool::LuaPackage::Impl
{
public:
	std::string				m_strName;
	LuaFuncRegList			m_listFuncReg;
	LuaEnumRegList			m_listEnumReg;
	LuaMetatableRegList		m_listMetatableReg;
	std::function<void()>	m_funcInit;
	LuaFunc					m_funcQuit;

public:
	Impl(
		const std::string& strName,
		const LuaFuncRegList& listFuncReg,
		const LuaEnumRegList& listEnumReg,
		const LuaMetatableRegList& listMetatableReg,
		std::function<void()> funcInit,
		LuaFunc funcQuit
	) : 
		m_strName(strName),
		m_listFuncReg(listFuncReg), m_listEnumReg(listEnumReg), m_listMetatableReg(listMetatableReg),
		m_funcInit(funcInit), m_funcQuit(funcQuit) {}
};

SDE_PackageTool::LuaPackage::LuaPackage(
	const std::string& strName,
	const LuaFuncRegList& listFuncReg,
	const LuaEnumRegList& listEnumReg,
	const LuaMetatableRegList& listMetatable,
	std::function<void()> funcInit,
	LuaFunc funcQuit
)
{
	m_pImpl = new Impl(strName, listFuncReg, listEnumReg, listMetatable, funcInit, funcQuit);
}

void SDE_PackageTool::LuaPackage::Initialize() const
{
	m_pImpl->m_funcInit();
}

const std::string& SDE_PackageTool::LuaPackage::GetName() const
{
	return m_pImpl->m_strName;
}

const SDE_PackageTool::LuaFuncRegList& SDE_PackageTool::LuaPackage::GetFuncRegList() const
{
	return m_pImpl->m_listFuncReg;
}

const SDE_PackageTool::LuaEnumRegList& SDE_PackageTool::LuaPackage::GetEnumRegList() const
{
	return m_pImpl->m_listEnumReg;
}

const SDE_PackageTool::LuaMetatableRegList& SDE_PackageTool::LuaPackage::GetMetatableRegList() const
{
	return m_pImpl->m_listMetatableReg;
}

SDE_PackageTool::LuaFunc SDE_PackageTool::LuaPackage::GetQuitFunc() const
{
	return m_pImpl->m_funcQuit;
}

SDE_PackageTool::LuaPackage::~LuaPackage()
{
	delete m_pImpl;
}

void SDE_PackageTool::SetLuaEnumList(lua_State* pState, const LuaEnumRegList& listEnumReg)
{
	if (lua_type(pState, -1) != LUA_TTABLE)
	{
		luaL_error(pState, "The object on the top of the stack isn't table.");
	}

	listEnumReg.Foreach(
		[&pState](const LuaEnumReg& regEnum)
		{
			lua_pushstring(pState, regEnum.name);
			lua_pushinteger(pState, regEnum.value);
			lua_rawset(pState, -3);
		}
	);
}

void SDE_PackageTool::SetLuaFuncList(lua_State* pState, const LuaFuncRegList& listFuncReg)
{
	if (lua_type(pState, -1) != LUA_TTABLE)
	{
		luaL_error(pState, "The object on the top of the stack isn't table.");
	}

	listFuncReg.Foreach(
		[&pState](const LuaFuncReg& regEnum)
		{
			lua_pushstring(pState, regEnum.name);
			lua_pushcfunction(pState, regEnum.func);
			lua_rawset(pState, -3);
		}
	);
}

void SDE_PackageTool::RegisterLuaMetatable(lua_State* pState, const LuaMetatableReg& regMetatable)
{
	luaL_newmetatable(pState, regMetatable.GetName().c_str());

	lua_pushstring(pState, "__index");
	lua_createtable(pState, 0, regMetatable.GetFuncRegList().GetSize());
	SetLuaFuncList(pState, regMetatable.GetFuncRegList());
	lua_rawset(pState, -3);

	lua_pushstring(pState, "__gc");
	lua_pushcfunction(pState, regMetatable.GetGCFunc());
	lua_rawset(pState, -3);

	lua_pop(pState, -1);
}

void SDE_PackageTool::SetLuaPackage(lua_State* pState, const LuaPackage& package)
{
	if (lua_type(pState, -1) != LUA_TTABLE)
	{
		luaL_error(pState, "The object on the top of the stack isn't table.");
	}

	// Call the package's initialization function.
	package.Initialize();

	// Create a table containing package functions and enumeration values.
	lua_pushstring(pState, package.GetName().c_str());
	lua_createtable(pState, 0, package.GetFuncRegList().GetSize() + package.GetEnumRegList().GetSize());
	{
		SetLuaFuncList(pState, package.GetFuncRegList());
		SetLuaEnumList(pState, package.GetEnumRegList());

		// Set the quit function for the package.
		lua_newtable(pState);
		{
			lua_pushstring(pState, "__gc");
			lua_pushcfunction(pState, package.GetQuitFunc());
			lua_rawset(pState, -3);
		}
		lua_setmetatable(pState, -2);
	}
	lua_rawset(pState, -3);

	// Register all metatables in the package.
	package.GetMetatableRegList().Foreach(
		[&pState](const SDE_PackageTool::LuaMetatableReg& regMetatable)
		{
			RegisterLuaMetatable(pState, regMetatable);
		}
	);
}