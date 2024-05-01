#pragma once
#include "SectionBase.h"
#include "SectionData.h"

class GraphicSection : public SectionBase<SectionData>
{
	static constexpr uint32_t SECTIONS = 16;

public:
	GraphicSection() :
		SectionBase(SECTIONS)
	{
	}
};

class UiSection : public SectionBase<SectionData>
{
	static constexpr uint32_t SECTIONS = 15;

public:
	UiSection() :
		SectionBase(SECTIONS)
	{
	}
};

class AudioSection : public SectionBase<SectionData>
{
	static constexpr uint32_t SECTIONS = 2;

public:
	AudioSection() :
		SectionBase(SECTIONS)
	{
	}
};

class FontSection : public SectionBase<SectionData>
{
public:
	FontSection() :
		SectionBase()
	{
	}
};

class VideoSection : public SectionBase<SectionData>
{
public:
	VideoSection() :
		SectionBase()
	{
	}
};
