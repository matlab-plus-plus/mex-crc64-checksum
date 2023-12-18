#pragma once

namespace codes
{
	enum class eReturnCode
	{
		SUCCESS,
		ARGUMENT_ERROR,
		FILE_NOT_FOUND_ERROR,
		FILE_OPEN_ERROR,
		UNKNOWN_ERROR,
		NUM_RETURN_CODES
	};

	template<eReturnCode E>
	requires (static_cast<int>(E) < static_cast<int>(eReturnCode::NUM_RETURN_CODES))
	inline constexpr int return_code{ static_cast<int>(E) };
}