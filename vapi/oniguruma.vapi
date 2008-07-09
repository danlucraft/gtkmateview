
namespace Oniguruma {

	[CCode (cname = "onig_new", cheader_filename = "oniguruma.h")]
	public static int onig_new(out RegexT regex, char* pattern, char* pattern_end,
							   OnigOptionType option, int enc, OnigSyntaxType syntax,
							   ref OnigErrorInfo err_info);

	[CCode (cname = "onig_error_code_to_str", cheader_filename = "oniguruma.h")]
	public static int error_code_to_string(char* err_buf, int err_code);

	[CCode (cname = "regex_t", cheader_filename = "oniguruma.h", free_function = "onig_free", ref_function="", unref_function="")]
	public class RegexT {
		[CCode (cname = "onig_search", cheader_filename = "oniguruma.h")]
		public int search(char* str, char* end, char* start,
						  char* range, Region region, OnigOptionType option);
		[CCode (cname = "onig_number_of_captures", cheader_filename = "oniguruma.h")]
		public int number_of_captures();
	}
	
	[CCode (cname = "OnigRegion", cheader_filename = "oniguruma.h", free_function = "onig_region_free", ref_function="", unref_function="")]
	public class Region {
		public int num_regs;
		public int[] beg;
		public int[] end;
		[CCode (cname = "onig_region_new", cheader_filename = "oniguruma.h")]
		public Region();
	}

	[CCode (cname="OnigOptionType*")]
	public struct OnigOptionType : int { }

	[CCode (cname="OnigEncoding*")]
	public struct OnigEncoding : int { }

	[CCode (cname="OnigSyntaxType*")]
	public struct OnigSyntaxType : int { }

	[CCode (cname="UChar")]
	public struct UChar : char { }

	namespace Option {
		[CCode (cname = "ONIG_OPTION_NONE", cheader_filename = "oniguruma.h")]
		public const OnigOptionType NONE;
		[CCode (cname = "ONIG_OPTION_IGNORECASE", cheader_filename = "oniguruma.h")]
        public const OnigOptionType IGNORECASE;
		[CCode (cname = "ONIG_OPTION_EXTEND", cheader_filename = "oniguruma.h")]
		public const OnigOptionType EXTEND;
		[CCode (cname = "ONIG_OPTION_MULTILINE", cheader_filename = "oniguruma.h")]
		public const OnigOptionType MULTILINE;
		[CCode (cname = "ONIG_OPTION_SINGLELINE", cheader_filename = "oniguruma.h")]
		public const OnigOptionType SINGLELINE;
		[CCode (cname = "ONIG_OPTION_FIND_LONGEST", cheader_filename = "oniguruma.h")]
		public const OnigOptionType FIND_LONGEST;
		[CCode (cname = "ONIG_OPTION_FIND_NOT_EMPTY", cheader_filename = "oniguruma.h")]
		public const OnigOptionType FIND_NOT_EMPTY;
		[CCode (cname = "ONIG_OPTION_NEGATE_SINGLELINE", cheader_filename = "oniguruma.h")]
		public const OnigOptionType NEGATE_SINGLELINE;
		[CCode (cname = "ONIG_OPTION_DONT_CAPTURE_GROUP", cheader_filename = "oniguruma.h")]
		public const OnigOptionType DONT_CAPTURE_GROUP;
		[CCode (cname = "ONIG_OPTION_CAPTURE_GROUP", cheader_filename = "oniguruma.h")]
		public const OnigOptionType CAPTURE_GROUP;
		[CCode (cname = "ONIG_OPTION_NOTBOL", cheader_filename = "oniguruma.h")]
		public const OnigOptionType NOTBOL;
		[CCode (cname = "ONIG_OPTION_NOTEOL", cheader_filename = "oniguruma.h")]
		public const OnigOptionType NOTEOL;
		[CCode (cname = "ONIG_OPTION_POSIX_REGION", cheader_filename = "oniguruma.h")]
		public const OnigOptionType POSIX_REGION;
		[CCode (cname = "ONIG_OPTION_MAXBIT", cheader_filename = "oniguruma.h")]
		public const OnigOptionType MAXBIT;
		[CCode (cname = "ONIG_OPTION_DEFAULT", cheader_filename = "oniguruma.h")]
		public const OnigOptionType DEFAULT;
	}

	namespace Encoding {
		[CCode (cname = "ONIG_ENCODING_ASCII", cheader_filename = "oniguruma.h")]
		public const OnigEncoding ASCII;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_1;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_2;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_3;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_4;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_5;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_6;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_7;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_8;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_9;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_10;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_11;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_13;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_14;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_15;
		// public const OnigEncoding ONIG_ENCODING_ISO_8859_16;
		[CCode (cname = "ONIG_ENCODING_UTF8", cheader_filename = "oniguruma.h")]
		public const OnigEncoding ONIG_ENCODING_UTF8;
		// public const OnigEncoding ONIG_ENCODING_UTF16_BE;
		// public const OnigEncoding ONIG_ENCODING_UTF16_LE;
		// public const OnigEncoding ONIG_ENCODING_UTF32_BE;
		// public const OnigEncoding ONIG_ENCODING_UTF32_LE;
		// public const OnigEncoding ONIG_ENCODING_EUC_JP;
		// public const OnigEncoding ONIG_ENCODING_EUC_TW;
		// public const OnigEncoding ONIG_ENCODING_EUC_KR;
		// public const OnigEncoding ONIG_ENCODING_EUC_CN;
		// public const OnigEncoding ONIG_ENCODING_SJIS;
		// public const OnigEncoding ONIG_ENCODING_KOI8_R;
		// public const OnigEncoding ONIG_ENCODING_CP1251;
		// public const OnigEncoding ONIG_ENCODING_BIG5;
		// public const OnigEncoding ONIG_ENCODING_GB18030;
	}

	namespace Syntax {
		// public const OnigSyntaxType ONIG_SYNTAX_ASIS;
		// public const OnigSyntaxType ONIG_SYNTAX_POSIX_BASIC;
		// public const OnigSyntaxType ONIG_SYNTAX_POSIX_EXTENDED;
		// public const OnigSyntaxType ONIG_SYNTAX_EMACS;
		// public const OnigSyntaxType ONIG_SYNTAX_GREP;
		// public const OnigSyntaxType ONIG_SYNTAX_GNU_REGEX;
		// public const OnigSyntaxType ONIG_SYNTAX_JAVA;
		// public const OnigSyntaxType ONIG_SYNTAX_PERL;
		// public const OnigSyntaxType ONIG_SYNTAX_PERL_NG;
		// public const OnigSyntaxType ONIG_SYNTAX_RUBY;
		[CCode (cname = "ONIG_SYNTAX_DEFAULT", cheader_filename = "oniguruma.h")]
		public const OnigSyntaxType DEFAULT;
	}

	[CCode (cname = "OnigErrorInfo", cheader_filename = "oniguruma.h")]
	public struct OnigErrorInfo {
		public OnigEncoding enc;
		public UChar* par;
		public UChar* par_end;
	}


}
