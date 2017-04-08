project( scintella_qt )
cmake_minimum_required(VERSION 3.1)
cmake_policy( SET CMP0020 NEW )
include( $ENV{QUARTZ_ROOT}/cmake/quartz.cmake )

qz_add_qt()

add_definitions( -DSCINTILLA_QT )
#add_definitions( -DMAKING_LIBRARY )
add_definitions( -DEXPORT_IMPORT_API )
add_definitions( -DSCI_LEXER )

set( VQ_INCLUDE_DIRS ${VQ_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} )
add_subdirectory( lexers )


vq_headers(
	AutoComplete.h
	CallTip.h
	CaseConvert.h
	CaseFolder.h
	Catalogue.h
	CellBuffer.h
	CharClassify.h
	ContractionState.h
	Decoration.h
	Document.h
	EditModel.h
	EditView.h
	Editor.h
	ExternalLexer.h
	FontQuality.h
	Indicator.h
	KeyMap.h
	LineMarker.h
	MarginView.h
	Partitioning.h
	PerLine.h
	PlatQt.h
	Position.h
	PositionCache.h
	RESearch.h
	RunStyles.h
	ScintillaBase.h
	ScintillaDocument.h
	ScintillaEdit.h
	ScintillaEditBase.h
	ScintillaQt.h
	Selection.h
	SparseVector.h
	SplitVector.h
	Style.h
	UniConversion.h
	UnicodeFromUTF8.h
	ViewStyle.h
	XPM.h
        ILexer.h
        Platform.h
        SciLexer.h
        Sci_Position.h
        Scintilla.h
        Accessor.h
        CharacterCategory.h
        CharacterSet.h
        LexAccessor.h
        LexerBase.h
        LexerModule.h
        LexerNoExceptions.h
        LexerSimple.h
        OptionSet.h
        PropSetSimple.h
        SparseState.h
        StringCopy.h
        StyleContext.h
        SubStyles.h
        WordList.h
        SymbolExportImport.h
)

vq_sources(
	AutoComplete.cxx
	CallTip.cxx
	CaseConvert.cxx
	CaseFolder.cxx
	Catalogue.cxx
	CellBuffer.cxx
	CharClassify.cxx
	ContractionState.cxx
	Decoration.cxx
	Document.cxx
	EditModel.cxx
	EditView.cxx
	Editor.cxx
	ExternalLexer.cxx
	Indicator.cxx
	KeyMap.cxx
	LineMarker.cxx
	MarginView.cxx
	PerLine.cxx
	PositionCache.cxx
	RESearch.cxx
	RunStyles.cxx
	ScintillaBase.cxx
	Selection.cxx
	Style.cxx
	UniConversion.cxx
	ViewStyle.cxx
	XPM.cxx
        Accessor.cxx
        CharacterCategory.cxx
        CharacterSet.cxx
        LexerBase.cxx
        LexerModule.cxx
        LexerNoExceptions.cxx
        LexerSimple.cxx
        PropSetSimple.cxx
        StyleContext.cxx
        WordList.cxx
        Main.cxx
        PlatQt.cpp
        ScintillaDocument.cpp
        ScintillaEdit.cpp
        ScintillaEditBase.cpp
        ScintillaQt.cpp
)

vq_create_app()
vq_install()
