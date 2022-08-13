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

		// Foreach all enum in the list and call the function for them.
		void Foreach(std::function<void(const LuaEnumReg&)> funcCalled) const;

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		LuaEnumRegList(const std::initializer_list<LuaEnumReg>& ilLuaEnumReg);
		~LuaEnumRegList();
	};

	class LuaFuncRegList
	{
	public:
		// Get the size of the func list.
		size_t GetSize() const;

		// Foreach all func in the list and call the function for them.
		void Foreach(std::function<void(const LuaFuncReg&)> funcCalled) const;

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		LuaFuncRegList(const std::initializer_list<LuaFuncReg>& ilLuaFuncReg);
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
			const LuaFuncRegList& listFuncReg,
			lua_CFunction funcGC = [](lua_State*)->int {}
		) :
			m_strName(strName), m_listFuncReg(listFuncReg), m_funcGC(funcGC) {}
	};

	class LuaMetatableRegList
	{
	public:
		// Get the size of the metatable list.
		size_t GetSize() const;

		// Foreach all metatable in the list and call the function for them.
		void Foreach(std::function<void(const LuaMetatableReg&)> funcCalled) const;

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		LuaMetatableRegList(const std::initializer_list<LuaMetatableReg>& ilMetatableReg);
		~LuaMetatableRegList();
	};

	class LuaPackage
	{
	public:
		// Call the initialization function.
		void Initialize() const;

		// Get the name of the package.
		const std::string& GetName() const;

		// Get the func list of the package.
		const LuaFuncRegList& GetFuncRegList() const;

		// Get the enum list of the package.
		const LuaEnumRegList& GetEnumRegList() const;

		// Get the metatable list of the package.
		const LuaMetatableRegList& GetMetatableRegList() const;

		// Get the quit function of the package.
		LuaFunc GetQuitFunc() const;

	private:
		class Impl;
		Impl* m_pImpl;

	public:
		LuaPackage(
			const std::string& strName,
			const LuaFuncRegList& listFuncReg,
			const LuaEnumRegList& listEnumReg,
			const LuaMetatableRegList& listMetatable,
			std::function<void()> funcInit = []()->void {},
			LuaFunc funcQuit = [](lua_State*)->int {}
		);
		~LuaPackage();
	};

	class LuaPackageManager
	{
	public:
		// Push a package into manager and return the index of the package.
		size_t Push(const LuaPackage& package);

		// Get the size of the package list.
		size_t GetSize() const;

		// Foreach all package in the list and call the function for them.
		void Foreach(std::function<void(const LuaPackage&)> funcCalled) const;

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
}

#endif // !_SDE_PACKAGE_TOOL_H_