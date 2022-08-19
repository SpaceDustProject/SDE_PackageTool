#ifndef _SDE_PACKAGE_TOOL_H_
#define _SDE_PACKAGE_TOOL_H_

#include <lua.hpp>

#include <string>
#include <functional>
#include <initializer_list>

#define SDE_API extern "C"

#define SDE_LUA_FUNC_X(FUNC_NAME, STATE_NAME) \
		SDE_API int FUNC_NAME(lua_State* STATE_NAME)

#define SDE_LUA_FUNC(FUNC_NAME) SDE_LUA_FUNC_X(FUNC_NAME, pState)

#ifdef _MSC_VER
#define SDE_PACKAGE_MAIN(PACKAGE_NAME)		\
		SDE_API __declspec(dllexport) int	\
		luaopen_ ## PACKAGE_NAME(lua_State* pState)
#else
#define SDE_PACKAGE_MAIN(PACKAGE_NAME)	\
		SDE_API int						\
		luaopen_ ## PACKAGE_NAME(lua_State* pState)
#endif // _MSC_VER

namespace SDE_PackageTool
{
	typedef lua_CFunction	LuaFunc;
	typedef luaL_Reg		LuaFuncReg;
	typedef void (*LuaPackageInitializer)(lua_State*);

	struct LuaEnumReg
	{
		const char* name;
		long long value;
	};

	class LuaEnumRegList
	{
	public:
		// Get the size of the enum list.
		size_t GetSize() const;

		// Traverse all enum in the list and call the function for them.
		void Traverse(std::function<void(const LuaEnumReg&)> funcCalled) const;

		LuaEnumRegList& operator=(const LuaEnumRegList& listEnumReg);

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		LuaEnumRegList(const std::initializer_list<LuaEnumReg>& ilLuaEnumReg);
		LuaEnumRegList(const LuaEnumRegList& listEnumReg);
		~LuaEnumRegList();
	};

	class LuaFuncRegList
	{
	public:
		// Get the size of the func list.
		size_t GetSize() const;

		// Traverse all func in the list and call the function for them.
		void Traverse(std::function<void(const LuaFuncReg&)> funcCalled) const;

		LuaFuncRegList& operator=(const LuaFuncRegList& listFuncReg);

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		LuaFuncRegList(const std::initializer_list<LuaFuncReg>& ilLuaFuncReg);
		LuaFuncRegList(const LuaFuncRegList& listFuncReg);
		~LuaFuncRegList();
	};

	class LuaMetatableReg
	{
	public:
		const std::string& GetName() const {
			return m_strName;
		}

		const LuaFuncRegList& GetFuncRegList() const {
			return m_listFuncReg;
		}

		LuaFunc	GetGCFunc() const {
			return m_funcGC;
		}

	private:
		std::string		m_strName;
		LuaFuncRegList	m_listFuncReg;
		LuaFunc			m_funcGC;

	public:
		LuaMetatableReg(
			const std::string& strName,
			const std::initializer_list<LuaFuncReg>& ilLuaFuncReg,
			lua_CFunction funcGC = [](lua_State*)->int {}
		) :
			m_strName(strName), m_listFuncReg(ilLuaFuncReg), m_funcGC(funcGC) {}
	};

	class LuaMetatableRegList
	{
	public:
		// Get the size of the metatable list.
		size_t GetSize() const;

		// Traverse all metatable in the list and call the function for them.
		void Traverse(std::function<void(const LuaMetatableReg&)> funcCalled) const;

		LuaMetatableRegList& operator=(const LuaMetatableRegList& listMetatableReg);

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		LuaMetatableRegList(const std::initializer_list<LuaMetatableReg>& ilMetatableReg);
		LuaMetatableRegList(const LuaMetatableRegList& listMetatableReg);
		~LuaMetatableRegList();
	};

	class LuaPackage
	{
	public:
		// Call the initialization function.
		void Initialize(lua_State* pState) const;

		// Get the name of the package.
		const std::string& GetName() const;

		// Get the func list of the package.
		const LuaFuncRegList& GetFuncRegList() const;

		// Get the quit function of the package.
		LuaFunc GetQuitFunc() const;

		LuaPackage& operator=(const LuaPackage& package);

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		LuaPackage(
			const std::string& strName,
			const std::initializer_list<LuaFuncReg>& ilLuaFuncReg,
			const std::initializer_list<LuaEnumReg>& ilLuaEnumReg,
			const std::initializer_list<LuaMetatableReg>& ilLuaMetatableReg,
			LuaPackageInitializer funcInit = [](lua_State*)->void {},
			LuaFunc funcQuit = [](lua_State*)->int {}
		);
		LuaPackage(const LuaPackage& package);

		~LuaPackage();
	};

	class LuaPackageManager
	{
	public:
		// Add a package into manager and return the index of the package.
		size_t Add(const LuaPackage& package);

		// Get the size of the package list.
		size_t GetSize() const;

		// Traverse all package in the list and call the function for them.
		void Traverse(std::function<void(const LuaPackage&)> funcCalled) const;

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		~LuaPackageManager();
		LuaPackageManager(const LuaPackageManager&) = delete;
		LuaPackageManager& operator=(const LuaPackageManager&) = delete;
		static LuaPackageManager& Instance() {
			static LuaPackageManager instance;
			return instance;
		}
	private:
		LuaPackageManager();
	};

	// Set all enum in the list into the table on the top of the stack.
	void SetLuaEnumList(lua_State* pState, const LuaEnumRegList& listEnumReg);

	// Set all functions in the list into the table on the top of the stack.
	void SetLuaFuncList(lua_State* pState, const LuaFuncRegList& listFuncReg);

	// Register the metatable into the registry of the state.
	void RegisterLuaMetatable(lua_State* pState, const LuaMetatableReg& regMetatable);

	// Register the package's metatable and set the package's data into the table on the top of the stack.
	void SetLuaPackage(lua_State* pState, const LuaPackage& package);

	// Traverse a table and call the function for its elements.
	void TraverseTable(lua_State* pState, int nIndex, std::function<bool()> funcCalled);

	// Create a userdata on the top of the stack and set a metatable for it.
	void* NewUserdata(lua_State* pState, size_t nSize, const std::string& strMetatableName);

	// Get userdata on the specified index and check its metatable.
	void* ToUserdata(lua_State* pState, int nIndex, const std::string& strMetatableName);
}

#endif // !_SDE_PACKAGE_TOOL_H_