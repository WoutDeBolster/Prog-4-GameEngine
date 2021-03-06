#pragma once

struct _TTF_Font;
namespace dae
{
	/**
	 * Simple RAII wrapper for an _TTF_Font
	 */
	class Font final
	{
	public:
		Font() = default;
		~Font();

		Font(const Font&) = delete;
		Font(Font&&) = delete;
		Font& operator= (const Font&) = delete;
		Font& operator= (const Font&&) = delete;

		_TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);

	private:
		_TTF_Font* m_Font;
		unsigned int m_Size;
	};
}
