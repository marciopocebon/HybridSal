/**
 * <b>SOFTWARE RIGHTS</b>
 * <p>
 * ANTLR 2.6.0 MageLang Insitute, 1998
 * <p>
 * We reserve no legal rights to the ANTLR--it is fully in the
 * public domain. An individual or company may do whatever
 * they wish with source code distributed with ANTLR or the
 * code generated by ANTLR, including the incorporation of
 * ANTLR, or its output, into commerical software.
 * <p>
 * We encourage users to develop software with ANTLR. However,
 * we do ask that credit is given to us for developing
 * ANTLR. By "credit", we mean that if you use ANTLR or
 * incorporate any source code into one of your programs
 * (commercial product, research project, or otherwise) that
 * you acknowledge this fact somewhere in the documentation,
 * research report, etc... If you like ANTLR and have
 * developed a nice tool with the output, please mention that
 * you developed it using ANTLR. In addition, we ask that the
 * headers remain intact in our source code. As long as these
 * guidelines are kept, we expect to continue enhancing this
 * system and expect to make other tools available as they are
 * completed.
 * <p>
 * The ANTLR gang:
 * @version ANTLR 2.6.0 MageLang Insitute, 1998
 * @author Terence Parr, <a href=http://www.MageLang.com>MageLang Institute</a>
 * @author <br>John Lilley, <a href=http://www.Empathy.com>Empathy Software</a>
 * @author <br><a href="mailto:pete@yamuna.demon.co.uk">Pete Wells</a>
 */

#include "antlr/MismatchedTokenException.hpp"
#include "antlr/String.hpp"

ANTLR_BEGIN_NAMESPACE(antlr)

MismatchedTokenException::MismatchedTokenException()
: RecognitionException("Mismatched Token: expecting any AST node","<AST>",1)
, token(0)
, node(nullASTptr)
{
}

// Expected range / not range
MismatchedTokenException::MismatchedTokenException(
	const ANTLR_USE_NAMESPACE(std)vector<ANTLR_USE_NAMESPACE(std)string>& tokenNames_,
	RefAST node_,
	int lower,
	int upper_,
	bool matchNot
) : RecognitionException("Mismatched Token")
  , tokenNames(tokenNames_)
  , token(0)
  , node(node_)
  , tokenText( (node_ ? node_->toString(): ANTLR_USE_NAMESPACE(std)string("<empty tree>")) )
  , mismatchType(matchNot ? NOT_RANGE : RANGE)
  , expecting(lower)
  , upper(upper_)
{
	fileName = "<AST>";
}

// Expected token / not token
MismatchedTokenException::MismatchedTokenException(
	const ANTLR_USE_NAMESPACE(std)vector<ANTLR_USE_NAMESPACE(std)string>& tokenNames_,
	RefAST node_,
	int expecting_,
	bool matchNot
) : RecognitionException("Mismatched Token")
  , tokenNames(tokenNames_)
  , token(0)
  , node(node_)
  , tokenText( (node_ ? node_->toString(): ANTLR_USE_NAMESPACE(std)string("<empty tree>")) )
  , mismatchType(matchNot ? NOT_TOKEN : TOKEN)
  , expecting(expecting_)
{
	fileName = "<AST>";
}

// Expected BitSet / not BitSet
MismatchedTokenException::MismatchedTokenException(
	const ANTLR_USE_NAMESPACE(std)vector<ANTLR_USE_NAMESPACE(std)string>& tokenNames_,
	RefAST node_,
	BitSet set_,
	bool matchNot
) : RecognitionException("Mismatched Token")
  , tokenNames(tokenNames_)
  , token(0)
  , node(node_)
  , tokenText( (node_ ? node_->toString(): ANTLR_USE_NAMESPACE(std)string("<empty tree>")) )
  , mismatchType(matchNot ? NOT_SET : SET)
  , set(set_)
{
	fileName = "<AST>";
}

// Expected range / not range
MismatchedTokenException::MismatchedTokenException(
	const ANTLR_USE_NAMESPACE(std)vector<ANTLR_USE_NAMESPACE(std)string>& tokenNames_,
	RefToken token_,
	int lower,
	int upper_,
	bool matchNot,
	const ANTLR_USE_NAMESPACE(std)string& fileName_
) : RecognitionException("Mismatched Token",fileName_,token_->getLine(),token_->getColumn())
  , tokenNames(tokenNames_)
  , token(token_)
  , node(nullASTptr)
  , tokenText(token_->getText())																
  , mismatchType(matchNot ? NOT_RANGE : RANGE)
  , expecting(lower)
  , upper(upper_)
{
}

// Expected token / not token
MismatchedTokenException::MismatchedTokenException(
	const ANTLR_USE_NAMESPACE(std)vector<ANTLR_USE_NAMESPACE(std)string>& tokenNames_,
	RefToken token_,
	int expecting_,
	bool matchNot,
	const ANTLR_USE_NAMESPACE(std)string& fileName_
) : RecognitionException("Mismatched Token",fileName_,token_->getLine(),token_->getColumn())
  , tokenNames(tokenNames_)
  , token(token_)
  , node(nullASTptr)
  , tokenText(token_->getText())
  , mismatchType(matchNot ? NOT_TOKEN : TOKEN)
  , expecting(expecting_)
{
}

// Expected BitSet / not BitSet
MismatchedTokenException::MismatchedTokenException(
	const ANTLR_USE_NAMESPACE(std)vector<ANTLR_USE_NAMESPACE(std)string>& tokenNames_,
	RefToken token_,
	BitSet set_,
	bool matchNot,
	const ANTLR_USE_NAMESPACE(std)string& fileName_
) : RecognitionException("Mismatched Token",fileName_,token_->getLine(),token_->getColumn())
  , tokenNames(tokenNames_)
  , token(token_)
  , node(nullASTptr)
  , tokenText(token_->getText())
  , mismatchType(matchNot ? NOT_SET : SET)
  , set(set_)
{
}

// deprecated As of ANTLR 2.7.0
ANTLR_USE_NAMESPACE(std)string MismatchedTokenException::getErrorMessage() const
{
	return getMessage();
}

ANTLR_USE_NAMESPACE(std)string MismatchedTokenException::getMessage() const
{
	ANTLR_USE_NAMESPACE(std)string s;
	switch (mismatchType) {
	case TOKEN:
		s += "expecting " + tokenName(expecting) + ", found '" + tokenText + "'";
		break;
	case NOT_TOKEN:
		s += "expecting anything but " + tokenName(expecting) + "; got it anyway";
		break;
	case RANGE:
		s += "expecting token in range: " + tokenName(expecting) + ".." + tokenName(upper) + ", found '" + tokenText + "'";
		break;
	case NOT_RANGE:
		s += "expecting token NOT in range: " + tokenName(expecting) + ".." + tokenName(upper) + ", found '" + tokenText + "'";
		break;
	case SET:
	case NOT_SET:
		{
			s += ANTLR_USE_NAMESPACE(std)string("expecting ") + (mismatchType == NOT_SET ? "NOT " : "") + "one of (";
			ANTLR_USE_NAMESPACE(std)vector<int> elems = set.toArray();
			for (int i = 0; i < (int) elems.size(); i++)
			{
				s += " ";
				s += tokenName(elems[i]);
			}
			s += "), found '" + tokenText + "'";
		}
		break;
	default:
		s = RecognitionException::getMessage();
		break;
	}
	return s;
}

ANTLR_USE_NAMESPACE(std)string MismatchedTokenException::tokenName(int tokenType) const
{
	if (tokenType == Token::INVALID_TYPE) {
		return "<Set of tokens>";
	}
	else if (tokenType < 0 || tokenType >= (int) tokenNames.size()) {
		return ANTLR_USE_NAMESPACE(std)string("<") + tokenType + ">";
	}
	else {
		return tokenNames[tokenType];
	}
}

ANTLR_USE_NAMESPACE(std)string MismatchedTokenException::toString() const {
	if (token) {
		return getFileLineString() + getMessage();
	}
	return getMessage();
}

#ifndef NO_STATIC_CONSTS
const int MismatchedTokenException::TOKEN;
const int MismatchedTokenException::NOT_TOKEN;
const int MismatchedTokenException::RANGE;
const int MismatchedTokenException::NOT_RANGE;
const int MismatchedTokenException::SET;
const int MismatchedTokenException::NOT_SET;
#endif

ANTLR_END_NAMESPACE
