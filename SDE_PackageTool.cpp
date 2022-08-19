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

void SDE_PackageTool::LuaEnumRegList::Traverse(std::function<void(const SDE_PackageTool::LuaEnumReg&)> funcCalled) const
{
	for (std::list<LuaEnumReg>::iterator iter = m_pImpl->m_listLuaEnumReg.begin();
		iter != m_pImpl->m_listLuaEnumReg.end(); iter++)
	{
		funcCalled(*iter);
	}
}

SDE_PackageTool::LuaEnumRegList& SDE_PackageTool::LuaEnumRegList::operator=(const LuaEnumRegList& listEnumReg)
{
	if (m_pImpl) delete m_pImpl;
	m_pImpl = new Impl(*listEnumReg.m_pImpl);
}

SDE_PackageTool::LuaEnumRegList::LuaEnumRegList(const std::initializer_list<LuaEnumReg>& ilLuaEnumReg)
{
	m_pImpl = new Impl(ilLuaEnumReg);
}

SDE_PackageTool::LuaEnumRegList::LuaEnumRegList(const LuaEnumRegList& listEnumReg)
{
	m_pImpl = new Impl(*listEnumReg.m_pImpl);
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

void SDE_PackageTool::LuaFuncRegList::Traverse(std::function<void(const SDE_PackageTool::LuaFuncReg&)> funcCalled) const
{
	for (std::list<LuaFuncReg>::iterator iter = m_pImpl->m_listLuaFuncReg.begin();
		iter != m_pImpl->m_listLuaFuncReg.end(); iter++)
	{
		funcCalled(*iter);
	}
}

SDE_PackageTool::LuaFuncRegList& SDE_PackageTool::LuaFuncRegList::operator=(const LuaFuncRegList& listFuncReg)
{
	if (m_pImpl) delete m_pImpl;
	m_pImpl = new Impl(*listFuncReg.m_pImpl);
}

SDE_PackageTool::LuaFuncRegList::LuaFuncRegList(const std::initializer_list<LuaFuncReg>& ilLuaFuncReg)
{
	m_pImpl = new Impl(ilLuaFuncReg);
}

SDE_PackageTool::LuaFuncRegList::LuaFuncRegList(const LuaFuncRegList& listFuncReg)
{
	m_pImpl = new Impl(*listFuncReg.m_pImpl);
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

void SDE_PackageTool::LuaMetatableRegList::Traverse(std::function<void(const LuaMetatableReg&)> funcCalled) const
{
	for (std::list<LuaMetatableReg>::iterator iter = m_pImpl->m_listMetatableReg.begin();
		iter != m_pImpl->m_listMetatableReg.end(); iter++)
	{
		funcCalled(*iter);
	}
}

SDE_PackageTool::LuaMetatableRegList& SDE_PackageTool::LuaMetatableRegList::operator=(const LuaMetatableRegList& listMetatableReg)
{
	if (m_pImpl) delete m_pImpl;
	m_pImpl = new Impl(*listMetatableReg.m_pImpl);
}

SDE_PackageTool::LuaMetatableRegList::LuaMetatableRegList(const std::initializer_list<LuaMetatableReg>& ilMetatableReg)
{
	m_pImpl = new Impl(ilMetatableReg);
}

SDE_PackageTool::LuaMetatableRegList::LuaMetatableRegList(const LuaMetatableRegList& listMetatableReg)
{
	m_pImpl = new Impl(*listMetatableReg.m_pImpl);
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
	LuaPackageInitializer	m_funcInit;
	LuaFunc					m_funcQuit;

public:
	Impl(
		const std::string& strName,
		const std::initializer_list<LuaFuncReg>& ilLuaFuncReg,
		const std::initializer_list<LuaEnumReg>& ilLuaEnumReg,
		const std::initializer_list<LuaMetatableReg>& ilLuaMetatableReg,
		LuaPackageInitializer funcInit,
		LuaFunc funcQuit
	) :
		m_strName(strName),
		m_listFuncReg(ilLuaFuncReg),
		m_listEnumReg(ilLuaEnumReg),
		m_listMetatableReg(ilLuaMetatableReg),
		m_funcInit(funcInit),
		m_funcQuit(funcQuit)
	{}
};

void SDE_PackageTool::LuaPackage::Initialize(lua_State* pState) const
{
	m_pImpl->m_funcInit(pState);
}

const std::string& SDE_PackageTool::LuaPackage::GetName() const
{
	return m_pImpl->m_strName;
}

const SDE_PackageTool::LuaFuncRegList& SDE_PackageTool::LuaPackage::GetFuncRegList() const
{
	return m_pImpl->m_listFuncReg;
}

SDE_PackageTool::LuaFunc SDE_PackageTool::LuaPackage::GetQuitFunc() const
{
	return m_pImpl->m_funcQuit;
}

SDE_PackageTool::LuaPackage& SDE_PackageTool::LuaPackage::operator=(const LuaPackage& package)
{
	if (m_pImpl) delete m_pImpl;
	m_pImpl = new Impl(*package.m_pImpl);
}

SDE_PackageTool::LuaPackage::LuaPackage(
	const std::string& strName,
	const std::initializer_list<LuaFuncReg>& ilLuaFuncReg,
	const std::initializer_list<LuaEnumReg>& ilLuaEnumReg,
	const std::initializer_list<LuaMetatableReg>& ilLuaMetatableReg,
	LuaPackageInitializer funcInit,
	LuaFunc funcQuit
)
{
	m_pImpl = new Impl(strName, ilLuaFuncReg, ilLuaEnumReg, ilLuaMetatableReg, funcInit, funcQuit);
}

SDE_PackageTool::LuaPackage::LuaPackage(const LuaPackage& package)
{
	m_pImpl = new Impl(*package.m_pImpl);
}

SDE_PackageTool::LuaPackage::~LuaPackage()
{
	delete m_pImpl;
}

class SDE_PackageTool::LuaPackageManager::Impl
{
public:
	std::list<SDE_PackageTool::LuaPackage> m_listPackage;
};

size_t SDE_PackageTool::LuaPackageManager::Add(const LuaPackage& package)
{
	m_pImpl->m_listPackage.push_back(package);
	return m_pImpl->m_listPackage.size() - 1;
}

size_t SDE_PackageTool::LuaPackageManager::GetSize() const
{
	return m_pImpl->m_listPackage.size();
}

void SDE_PackageTool::LuaPackageManager::Traverse(std::function<void(const LuaPackage&)> funcCalled) const
{
	for (std::list<SDE_PackageTool::LuaPackage>::iterator iter = m_pImpl->m_listPackage.begin();
		iter != m_pImpl->m_listPackage.end(); iter++)
	{
		funcCalled(*iter);
	}
}

SDE_PackageTool::LuaPackageManager::LuaPackageManager()
{
	m_pImpl = new Impl();
}

SDE_PackageTool::LuaPackageManager::~LuaPackageManager()
{
	delete m_pImpl;
}

void SDE_PackageTool::SetLuaEnumList(lua_State* pState, const LuaEnumRegList& listEnumReg)
{
	if (lua_type(pState, -1) != LUA_TTABLE)
	{
		luaL_error(pState, "The object on the top of the stack isn't table.");
	}

	listEnumReg.Traverse(
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

	listFuncReg.Traverse(
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
	package.Initialize(pState);

	// Create a table containing package functions and enumeration values.
	lua_pushstring(pState, package.GetName().c_str());
	lua_createtable(pState, 0, package.GetFuncRegList().GetSize());
	{
		SetLuaFuncList(pState, package.GetFuncRegList());

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
}

void SDE_PackageTool::TraverseTable(lua_State* pState, int nIndex, std::function<bool()> funcCalled)
{
	if (!lua_istable(pState, -1))
	{
		luaL_error(pState, "The object on the top of the stack isn't table.");
	}
	
	bool bContinue = true;
	lua_pushnil(pState);
	while (bContinue && lua_next(pState, nIndex))
	{
		bContinue = funcCalled();
		if (bContinue) {
			lua_pop(pState, 1);
		}
		else lua_pop(pState, 2);
	}
}

void* SDE_PackageTool::NewUserdata(lua_State* pState, size_t nSize, const std::string& strMetatableName)
{
	void* pUserdata = lua_newuserdata(pState, nSize);
	luaL_setmetatable(pState, strMetatableName.c_str());
	return pUserdata;
}

void* SDE_PackageTool::ToUserdata(lua_State* pState, int nIndex, const std::string& strMetatableName)
{
	void* pUserdata = luaL_checkudata(pState, nIndex, strMetatableName.c_str());
	return pUserdata;
}