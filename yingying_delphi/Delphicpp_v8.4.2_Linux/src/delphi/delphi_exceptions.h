/**
 * @file delphi_exceptions.h
 * @brief warnings/exceptions occurring in classes CDelphiData and CDelphiDataMarshal
 *
 * @author Chuan Li, chuanli@clemson.edu
 *
 * These warnings and exceptions should inherit from the classes CWarning and CException in order to
 * keep track the number of warnings and maintain consistent format.
 */

#ifndef DELPHI_EXCEPTIONS_H_
#define DELPHI_EXCEPTIONS_H_

#include "../interface/exceptions.h"

/**
 * user-specified &epsilon in one medium is invalid
 */
class CInvalidEpsInMedium : public CException
{
   public:
      CInvalidEpsInMedium(const delphi_integer& iMedium)
      {
         cerr << "ERROR OCCURS DUE TO DIELECTRIC IN MEDIUM NUMBER " << iMedium << "\" < 1.0 " << endl;
         cerr << "\t DELPHI IS NOT ABLE TO DEAL WITH EPS < 1.0. THEREFORE EXITING... " << endl;
      }
};

/**
 * obsolete object types
 */
class CIsAnObjectType : public CException
{
   public:
      CIsAnObjectType(const string& strObject)
      {
         cerr << "OBJECT TYPES (SPHERE, CYLINDER, CONE AND BOX) ARE NO LONG SUPPORTED IN DELPHI C++" << endl;
         cerr << "\t USE ProNOI TO GENERATE ATOMIC STYLE OBJECTS INSTEAD AND TRY AGAIN... " << endl;
      }
};

/**
 * no atom(s) read from the input file for a molecule
 */
class CNoAtomsInMolecule : public CException
{
   public:
      CNoAtomsInMolecule(const delphi_integer& iObject)
      {
         cerr << "OBJECT " << iObject << " IS A MOLECULE WITH NO ATOMS (TOTAL ATOM NUMBER = 0)" << endl;
         cerr << "\t CHECK THE INPUT FILES AND TRY AGAIN... " << endl;
      }
};

/**
 * no boundary elements and uniform dielectric flag
 */
class CNoBndyAndDielec : public CException
{
   public:
      CNoBndyAndDielec(shared_ptr<CTimer> pTimer)
      {
         cerr << "EXITING AS NO BOUNDARY ELEMENTS AND UNIFORM DIELECTRIC EXIT FLAG HAS BEEN SET" << endl;
         pTimer->exit();
      }
};

/**
 * no linit or nonit is specified while autoc = false
 */
class CBadAutoConvergence : public CException
{
   public:
   CBadAutoConvergence(const bool& bAutoConverge)
      {
         cerr << "EXITING AS AUTOC = " << bAutoConverge << " AND NO ITERATION NUMBER IS SPECIFIED" << endl;
         cerr << "\t SET \"LINIT\" OR \"NONIT\" NONZERO IN THE PARAMTER FILE AND TRY AGAIN... " << endl;
      }
};


/**
 * PERFIL IS A NEGATIVE NUMBER 
 */
class CBadPERFIL : public CException
{
   public:
   CBadPERFIL()
      {
         cerr << " PERFIL CANNOT BE ZERO OR NEGATIVE. TRY A VALUE >= 20. " << endl;
      }
};


/**
 * ACENTER is mandatory for focussing runs.
 */
class CNoAcenter: public CException
{
   public:
   CNoAcenter()
      {
        cerr << "ACENTER MUST BE SPECIFIED IN THE PARAMETER FILE WHEN USING FOCUSSING BOUNDARY CONDITION (bndcon=3)" << endl;
		cerr << "\t CHECK THE PARAMETER FILE AND TRY AGAIN... " << endl;
      }
};

/**
 * unrecognized statement in the paramter file
 */
class CBadStatementAssignment : public CWarning
{
   public:
      CBadStatementAssignment(const string & strArgument, const string & strStatement)
      {
         cwarn << "UNRECOGNIZED STATEMENT \"" << strStatement << " = " << strArgument << "\" ";
         cwarn << "(DEFAULT VALUE IS USED)" << endl;
      }
};

/**
 * user-specified nonit is out of range
 */
class COutOfRange_NONIT : public CWarning
{
   public:
   COutOfRange_NONIT(int& iNonIterateNum)
      {
         if (30 > iNonIterateNum)
            cwarn << "REQUIRES AT LEAST 30 NONLINEAR ITERATIONS ";
         else
            cwarn << "THE INPUT NONIT = " << iNonIterateNum << " IS OUT OF RANGE [0,10000] ";
         iNonIterateNum = 30;
         cwarn << "(RESET NONIT = " << iNonIterateNum << " ITERATIONS)\n";
      }
};

/**
 * unknown format of user-specified output PHI file
 */
class COutUnknownPHIFormat : public CWarning
{
   public:
      COutUnknownPHIFormat(const string&  strFormat)
      {
         cwarn << "UNKNOWN WRITE-OUT PHIMAP FILE FORMAT " << strFormat << " (DEFAULT PHIMAP FILE FORMAT IS USED)" << endl;
      }
};

/**
 * obsolete format option, PDBA, for output SCRG file
 */
class COutOBSOLETEPDBAFormat : public CWarning
{
   public:
      COutOBSOLETEPDBAFormat(const string& strFormat)
      {
         cwarn << "WRITE-OUT OPTION " << strFormat << " NO LONGER SUPPORTED!" << " (DEFAULT SCRG FORMAT IS USED)" << endl;
      }
};

/**
 * unrecognized function in the parameter file
 */
class CUnknownFunction : public CWarning
{
   public:
      CUnknownFunction(const string& strFuncName)
      {
         cwarn << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
         cwarn << " The function specifier   " << strFuncName << " is" << endl;
         cwarn << " not recognized. Therefore the function will not be processed " << endl;
         cwarn << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
       }
};

/**
 * negative dielectric constants
 */
class CMinusDielec : public CWarning
{
   public:
      CMinusDielec(const delphi_real& fExDielec, const delphi_real& fInDielec)
      {
         cwarn << "NEGATIVE DIELECTRIC CONSTANT(S): OUT = " << fExDielec << ", IN = " << fInDielec;
         cwarn << " (RESET TO BE THEIR ABSOLUTE VALUE(S))" << endl;
       }
};

/**
 * PDB file is determined as unformatted
 */
class CToUnformattedFile : public CWarning
{
   public:
      CToUnformattedFile(const string& strFile, const string& strASCI)
      {
         cwarn << "MORE THAN 10 CHARACTERS OUT OF THE FIRST 80 CHARACTERS IN THE FILE " << strFile << " ARE NOT IN THE LIST OF ASCI \n"
              << "<" << strASCI << "> (RESET THE PDB FILE FORMAT TO BE \"UNFORMATTED\")" << endl;
      }
};

/**
 * part of the system is outside the box
 */
class CSystemOutsideBox : public CWarning
{
   public:
      CSystemOutsideBox()
      {
         cwarn << "PART OF SYSTEM OUTSIDE THE BOX!" << endl;
      }
};

/**
 * read and write unformatted PDB file at the same time
 */
class CReadWriteUnformatPdb : public CWarning
{
   public:
      CReadWriteUnformatPdb(bool& bOutPdbFormat)
      {
         cwarn << "CANNOT WRITE AN UNFORMATTED PDB FILE, WHILE READING IN AN UNFORMATTED PDB FILE (THE WRITE OPTION IS DISABLED)" << endl;

         bOutPdbFormat = false;
      }
};

/**
 * read and write unformatted FRC file at the same time
 */
class CReadWriteUnformatFrc : public CWarning
{
   public:
      CReadWriteUnformatFrc(bool& bOutFrcFormat)
      {
         cwarn << "CANNOT WRITE AN UNFORMATTED FRC FILE, WHILE READING IN AN UNFORMATTED PDB FILE (WRITE OPTION IS DISABLED)" << endl;

         bOutFrcFormat = false;
      }
};

/**
 * input CONFRA is out of range
 */
class COutOfRange_CONFRA : public CWarning
{
   public:
   COutOfRange_CONFRA(int& iConvergeFract)
      {
         cwarn << "THE INPUT CONFRA = " << iConvergeFract << " IS OUT OF RANGE [1,100] ";
         iConvergeFract = 1;
         cwarn << "(RESET TO DEFAULT VALUE CONFRA = " << iConvergeFract << ")\n";
      }
};

/**
 * input PERFIL is less than 20
 */
class CSmall_PERFIL : public CWarning
{
   public:
   CSmall_PERFIL(delphi_real& fPercentageFill)
      {
         cwarn << "THE INPUT PERFIL = " << fPercentageFill << " IS SMALL WHICH MAKES THE BOX UNUSUALLY LARGE AND INCREASES THE COMPUTATION TIME. USE A VALUE LARGER THAN 20. ";
      }
};

 
/**
 * input CONINT is out of range
 */
class COutOfRange_CONINT : public CWarning
{
   public:
   COutOfRange_CONINT(int& iIterateInterval)
      {
         cwarn << "THE INPUT CONINT = " << iIterateInterval << " IS OUT OF RANGE [1,100] ";
         iIterateInterval = 10;
         cwarn << "(RESET TO DEFAULT VALUE CONINT = " << iIterateInterval << ")\n";
      }
};

/**
 * input EXDI is out of range
 */
class COutOfRange_EXDI : public CWarning
{
   public:
   COutOfRange_EXDI(delphi_real& fExDielec)
      {
         cwarn << "THE INPUT EXDI = " << fExDielec << " IS OUT OF RANGE (0.0,1000.0] ";
         fExDielec = 80.0;
         cwarn << "(RESET TO DEFAULT VALUE EXDI = " << fExDielec << ")\n";
      }
};

/**
 * obsolete spherical interpolation of charges to grids
 */
class CSphericalCrgIntelp : public CWarning
{
   public:
   CSphericalCrgIntelp(bool& bCrgInterplateType)
      {
         cwarn << "SPHERICAL INTERPOLATION OF CHARGES TO GRIDS IS OBSOLETED " ;
         cwarn << "(USING LINEAR CUBIC INTERPOLATION INSTEAD) \n";
         bCrgInterplateType = false;
      }
};

/**
 * input GRDCON is out of range
 */
class COutOfRange_GRDCON : public CWarning
{
   public:
   COutOfRange_GRDCON(delphi_real& fGridConverge)
      {
         cwarn << "THE INPUT GRDCON = " << fGridConverge << " IS OUT OF RANGE [0.0,100.0] ";
         fGridConverge = 0.0;
         cwarn << "(RESET TO DEFAULT VALUE GRDCON = " << fGridConverge << ")\n";
      }
};

/**
 * input GSIZE is out of range
 */
class COutOfRange_GSIZE : public CWarning
{
   public:
   COutOfRange_GSIZE(delphi_integer& iGrid)
      {
         cwarn << "THE INPUT GSIZE = " << iGrid << " IS OUT OF RANGE [5,2000] ";
         iGrid = 0;
         cwarn << "(RESET TO DEFAULT VALUE GSIZE = " << iGrid << ")\n";
      }
};

/**
 * input INDI is out of range
 */
class COutOfRange_INDI : public CWarning
{
   public:
   COutOfRange_INDI(delphi_real& fInDielec)
      {
         cwarn << "THE INPUT INDI = " << fInDielec << " IS OUT OF RANGE [5,2000] ";
         fInDielec = 2.0;
         cwarn << "(RESET TO DEFAULT VALUE INDI = " << fInDielec << ")\n";
      }
};

/**
 * input SALT is out of range
 */
class COutOfRange_SALT : public CWarning
{
   public:
   COutOfRange_SALT(delphi_real& fSalt)
      {
         cwarn << "THE INPUT SALT = " << fSalt << " IS OUT OF RANGE [0.0,10.0] ";
         fSalt = 0.0;
         cwarn << "(RESET TO DEFAULT VALUE SALT = " << fSalt << ")\n";
      }
};

/**
 * input IONRAD is out of range
 */
class COutOfRange_IONRAD : public CWarning
{
   public:
   COutOfRange_IONRAD(delphi_real& fIonRadius)
      {
         cwarn << "THE INPUT IONRAD = " << fIonRadius << " IS OUT OF RANGE [0.0,10.0] ";
         fIonRadius = 2.0;
         cwarn << "(RESET TO DEFAULT VALUE IONRAD = " << fIonRadius << ")\n";
      }
};

/**
 * input LINIT is out of range
 */
class COutOfRange_LINIT : public CWarning
{
   public:
   COutOfRange_LINIT(int& iLinIterateNum)
      {
         cwarn << "THE INPUT LINIT = " << iLinIterateNum << " IS OUT OF RANGE (10,10000] ";
         iLinIterateNum = 11;
         cwarn << "(RESET TO LINIT = " << iLinIterateNum << ")\n";
      }
};

/**
 * input MAXC is out of range
 */
class COutOfRange_MAXC : public CWarning
{
   public:
   COutOfRange_MAXC(delphi_real& fMaxc)
      {
         cwarn << "THE INPUT MAXC = " << fMaxc << " IS OUT OF RANGE (0.0,1.0) ";
         fMaxc = 0.01;
         cwarn << "(RESET TO MAXC = " << fMaxc << ")\n";
      }
};

/**
 * input PRBRAD is out of range
 */
class COutOfRange_PRBRAD : public CWarning
{
   public:
   COutOfRange_PRBRAD(delphi_real& fPrbrad)
      {
         cwarn << "THE INPUT PRBRAD = " << fPrbrad << " IS OUT OF RANGE [0.0,10.0) ";
         fPrbrad = 1.4;
         cwarn << "(RESET TO PRBRAD = " << fPrbrad << ")\n";
      }
};

/**
 * input PRBRAD2 is out of range
 */
class COutOfRange_PRBRAD2 : public CWarning
{
   public:
   COutOfRange_PRBRAD2(delphi_real& fPrbrad)
      {
         cwarn << "THE INPUT PRBRAD2 = " << fPrbrad << " IS OUT OF RANGE [0.0,10.0) ";
         fPrbrad = -1.0;
         cwarn << "(RESET TO PRBRAD2 = " << fPrbrad << ")\n";
      }
};

/**
 * input RELFAC is out of range
 */
class COutOfRange_RELFAC : public CWarning
{
   public:
   COutOfRange_RELFAC(delphi_real& fSpectralRadius)
      {
         cwarn << "THE INPUT RELFAC = " << fSpectralRadius << " IS OUT OF RANGE (0.0,1.0) ";
         fSpectralRadius = 0.9975;
         cwarn << "(RESET TO DEFAULT VALUE RELFAC = " << fSpectralRadius << ")\n";
      }
};

/**
 * input RELPAR is out of range
 */
class COutOfRange_RELPAR : public CWarning
{
   public:
   COutOfRange_RELPAR(delphi_real& fRelaxParam)
      {
         cwarn << "THE INPUT RELPAR = " << fRelaxParam << " IS OUT OF RANGE [0.0,2.0] ";
         fRelaxParam = 1.0;
         cwarn << "(RESET TO DEFAULT VALUE RELPAR = " << fRelaxParam << ")\n";
      }
};

/**
 * input RMSC is out of range
 */
class COutOfRange_RMSC : public CWarning
{
   public:
   COutOfRange_RMSC(delphi_real& fRmsc)
      {
         cwarn << "THE INPUT RMSC = " << fRmsc << " IS OUT OF RANGE (0.0,1.0) ";
         fRmsc = 0.0;
         cwarn << "(RESET TO DEFAULT VALUE RMSC = " << fRmsc << ")\n";
      }
};

/**
 * input SALT2 is out of range
 */
class COutOfRange_SALT2 : public CWarning
{
   public:
   COutOfRange_SALT2(delphi_real& fSalt2)
      {
         cwarn << "THE INPUT SALT2 = " << fSalt2 << " IS OUT OF RANGE [0.0,10.0] ";
         fSalt2 = 0.0;
         cwarn << "(RESET TO DEFAULT VALUE SALT2 = " << fSalt2 << ")\n";
      }
};

/**
 * input SCALE is out of range
 */
class COutofRange_SCALE : public CWarning
{
   public:
   COutofRange_SCALE(delphi_real& fScale)
      {
         cwarn << "THE INPUT SCALE = " << fScale << " IS OUT OF RANGE (0.0,40.0) ";
         fScale = 2.0;
         cwarn << "(RESET TO DEFAULT VALUE SCALE = " << fScale << ")\n";
      }
};

/**
 * input VAL+1 is out of range
 */
class COutOfRange_VALPLUS1 : public CWarning
{
   public:
   COutOfRange_VALPLUS1(int& iValPlus1)
      {
         cwarn << "THE INPUT VAL+1 = " << iValPlus1 << " IS OUT OF RANGE [1,10] ";
         iValPlus1 = 1;
         cwarn << "(RESET TO DEFAULT VALUE VAL+1 = " << iValPlus1 << ")\n";
      }
};

/**
 * input VAL-1 is out of range
 */
class COutOfRange_VALMINUS1 : public CWarning
{
   public:
   COutOfRange_VALMINUS1(int& iValMinus1)
      {
         cwarn << "THE INPUT VAL-1 = " << iValMinus1 << " IS OUT OF RANGE [1,10] ";
         iValMinus1 = 1;
         cwarn << "(RESET TO DEFAULT VALUE VAL-1 = " << iValMinus1 << ")\n";
      }
};

/**
 * input VAL+2 is out of range
 */
class COutOfRange_VALPLUS2 : public CWarning
{
   public:
   COutOfRange_VALPLUS2(int& iValPlus2)
      {
         cwarn << "THE INPUT VAL+2 = " << iValPlus2 << " IS OUT OF RANGE [1,10] ";
         iValPlus2 = 0;
         cwarn << "(RESET TO DEFAULT VALUE VAL+2 = " << iValPlus2 << ")\n";
      }
};

/**
 * input VAL-2 is out of range
 */
class COutOfRange_VALMINUS2 : public CWarning
{
   public:
   COutOfRange_VALMINUS2(int& iValMinus2)
      {
         cwarn << "THE INPUT VAL-2 = " << iValMinus2 << " IS OUT OF RANGE [1,10] ";
         iValMinus2 = 0;
         cwarn << "(RESET TO DEFAULT VALUE VAL-2 = " << iValMinus2 << ")\n";
      }
};

/**
 * input ATPODS is out of range
 */
class COutOfRange_ATPODS : public CWarning
{
   public:
   COutOfRange_ATPODS(delphi_real& fPotentialUpperBond)
      {
         cwarn << "THE INPUT ATPODS = " << fPotentialUpperBond << " IS OUT OF RANGE (1.0,10.0) ";
         fPotentialUpperBond = 0.5;
         cwarn << "(RESET TO DEFAULT VALUE ATPODS = " << fPotentialUpperBond << ")\n";
      }
};

/**
 * input TEMPER is out of range
 */
class COutOfRange_TEMPER : public CWarning
{
   public:
   COutOfRange_TEMPER(delphi_real& fTemper)
      {
         cwarn << "THE INPUT TEMPER = " << fTemper << " IS OUT OF RANGE [0.0,1000.0] ";
         fTemper = 297.3342119;
         cwarn << "(RESET TO DEFAULT VALUE TEMPER = " << fTemper << ")\n";
      }
};

/**
 * input VDROPX/VDROPY/VDROPZ is out of range
 */
class COutOfRange_VDROP : public CWarning
{
   public:
   COutOfRange_VDROP(delphi_real& fVdrop)
      {
         cwarn << "THE INPUT VDROP (X,Y, OR Z) = " << fVdrop << " IS OUT OF RANGE [0.0,1000.0] ";
         fVdrop = 0.0;
         cwarn << "(RESET TO DEFAULT VALUE VDROP = " << fVdrop << ")\n";
      }
};

/**
 * input surface distance is a bad value - negative or more than 10.
 */

class CBad_SURFDIST : public CWarning
{
    public:
    CBad_SURFDIST(int& zetaOn)
    {
      zetaOn = 0;
      cwarn << " SURFACE POTENTIAL CALCULATIONS HAVE BEEN TURNED OFF DUE TO ONE OF THE FOLLOWING REASONS\n";
      cwarn << "    -- SURFDIST IS > 10.0" << endl;
      cwarn << "    -- SURFDIST IS < 0.0" << endl;
      cwarn << "    -- GAUSSIAN MODULE IS ON. " << endl;
    }
};

/**
 * input function has no parameter(s)
 */
class CEmptyParameter_FUNCTION : public CWarning
{
   public:
   CEmptyParameter_FUNCTION(const string& strFunction)
      {
         cwarn << "FUNCTION \"" << strFunction << "\" HAS NO PARAMETER(S) (SKIP THIS FUNCTION)\n";
      }
};

/**
 * unknown parameter for specified function
 */
class CUnknownParameter_FUNCTION : public CWarning
{
   public:
   CUnknownParameter_FUNCTION(const string& strFunction, const string& strParameter)
      {
         cwarn << "UNKNOWN PARAMTER \"" << strParameter << "\" IN FUNCTION \"" << strFunction << "\" ";
         cwarn << "(THIS PARAMETER IS SKIPPED)\n";
      }
};

/**
 * obsolete statement
 */
class CObsoleteStatement : public CWarning
{
   public:
   CObsoleteStatement(const string& strStatement)
      {
         cwarn << "STATEMENT \"" << strStatement << "\" IS OBSOLETE ";
         cwarn << "(TAKING NO ACTION ON THIS STATEMENT)\n";
      }
};

/**
 * obsolete function
 */
class CObsoleteFunction : public CWarning
{
   public:
   CObsoleteFunction(const string& strFunction)
      {
         cwarn << "FUNCTION \"" << strFunction << "\" IS OBSOLETE ";
         cwarn << "(TAKING NO ACTION ON THIS FUNCTION)\n";
      }
};

/**
 * write(off) presents in the parameter file
 */
class CUncondionalOff_WRITE : public CWarning
{
   public:
   CUncondionalOff_WRITE()
      {
         cwarn << "WRITE(OFF): EVERYTHING DESCRIBED IN PREVIOUS WRITE FUNCTION IS TURNED OFF (NO OUTPUT FILE WILL BE PRODUCED)\n";
      }
};

#endif // DELPHI_EXCEPTIONS_H_
