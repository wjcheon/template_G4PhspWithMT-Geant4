// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// 	Author: W.J. Cheon
//  Major:
//  Radiolodical Science, Yonsei Univ., Korea. (B.S)
//  Communication and Information Eng., Computer Eng.,Yonsei Univ., Korea (B.Eng)
//  Medical Physics, Sungkyunkwan Univ., Korea (Ph.D integrated course)
//  Email: wonjoongcheon@gmail.com
//

#include "TrackingAction.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"

TrackingAction::TrackingAction()
:G4UserTrackingAction()
{;}

void TrackingAction::PostUserTrackingAction(const G4Track* track) {


}
