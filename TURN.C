/* TURN --------------------------------------- */




void pKoloTudi()
{ Turn3DTudi();ShowBasis();if(!fBasisOnly){InitBasis(&B);ShowImage();} }

void pKoloSudi()
{ Turn3DSudi();ShowBasis();if(!fBasisOnly){InitBasis(&B);ShowImage();} }

void pKoloTop()
{ Turn3DTop();ShowBasis();if(!fBasisOnly){InitBasis(&B);ShowImage();} }

void pKoloBut()
{ Turn3DBut();ShowBasis();if(!fBasisOnly){InitBasis(&B);ShowImage();} }

void pKoloRig()
{ Turn3DRig();ShowBasis();if(!fBasisOnly){InitBasis(&B);ShowImage();} }

void pKoloLef()
{ Turn3DLef();ShowBasis();if(!fBasisOnly){InitBasis(&B);ShowImage();} }


void pStandart()
{
  B.Ox.x=1;B.Ox.y=0;B.Ox.z=0;
  B.Oy.x=0;B.Oy.y=0;B.Oy.z=1;
  B.Oz.x=0;B.Oz.y=1;B.Oz.z=0;
  ShowBasis();if(!fBasisOnly){ InitBasis(&B);ShowImage(); }
}
