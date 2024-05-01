#pragma once

#include <deque>
#include <string>
#include <vector>

#include "MaterialData.h"
#include "ScriptData.h"
#include "SectionBase.h"

class ScriptSection : public SectionBase<ScriptData>
{
	inline static const std::string MAT_SEC_NAME = "MaterialSection";

public:
	ScriptSection();

	void Init(FileReader *pFileReader, const bool &present, const bool &matPresent, std::deque<SecInfo> &secInfos);

	virtual std::vector<uint32_t> SecSizes() const override;

protected:
	void build(const std::wstring &inputFolder) override;

	void loadSections(std::deque<SecInfo> &secInfos) override;

	void unpack(const std::wstring &outputFolder) const override;

	void writeSections(FileWriter &fileWriter) const override;

private:
	void loadMaterials();

	void writeMaterials(FileWriter &fileWriter) const;

private:
	std::vector<MaterialData> m_matData = {};
	bool m_matPresent                   = false;
};
