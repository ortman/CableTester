<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="snx_con" urn="urn:adsk.eagle:library:31813248">
<packages>
<package name="KLS1-603C-SMT" urn="urn:adsk.eagle:footprint:42556911/1" library_version="35">
<smd name="1" x="-38.1" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="2" x="-35.56" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="3" x="-33.02" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="4" x="-30.48" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="5" x="-27.94" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="6" x="-25.4" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="7" x="-22.86" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="8" x="-20.32" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="9" x="-17.78" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="10" x="-15.24" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="11" x="-12.7" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="12" x="-10.16" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="13" x="-7.62" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="14" x="-5.08" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="15" x="-2.54" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="16" x="0" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="17" x="2.54" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="18" x="5.08" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="19" x="7.62" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="20" x="10.16" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="21" x="12.7" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="22" x="15.24" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="23" x="17.78" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="24" x="20.32" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="25" x="22.86" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="26" x="25.4" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="27" x="27.94" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="28" x="30.48" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="29" x="33.02" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="30" x="35.56" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="31" x="38.1" y="0" dx="2.54" dy="1.27" layer="1" rot="R90"/>
<smd name="32" x="38.1" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="33" x="35.56" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="34" x="33.02" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="35" x="30.48" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="36" x="27.94" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="37" x="25.4" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="38" x="22.86" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="39" x="20.32" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="40" x="17.78" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="41" x="15.24" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="42" x="12.7" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="43" x="10.16" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="44" x="7.62" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="45" x="5.08" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="46" x="2.54" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="47" x="0" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="48" x="-2.54" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="49" x="-5.08" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="50" x="-7.62" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="51" x="-10.16" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="52" x="-12.7" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="53" x="-15.24" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="54" x="-17.78" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="55" x="-20.32" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="56" x="-22.86" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="57" x="-25.4" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="58" x="-27.94" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="59" x="-30.48" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="60" x="-33.02" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="61" x="-35.56" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<smd name="62" x="-38.1" y="0" dx="2.54" dy="1.27" layer="16" rot="R90"/>
<wire x1="-42.52" y1="3.3" x2="42.52" y2="3.3" width="0.127" layer="51"/>
<wire x1="-42.52" y1="3.3" x2="-42.52" y2="19" width="0.127" layer="51"/>
<wire x1="-42.52" y1="19" x2="42.52" y2="19" width="0.127" layer="51"/>
<wire x1="42.52" y1="19" x2="42.52" y2="3.3" width="0.127" layer="51"/>
<text x="-40.64" y="5.08" size="1.27" layer="51">1</text>
<text x="39.37" y="5.08" size="1.27" layer="51">31</text>
</package>
<package name="KLS1-603C-SLOT" urn="urn:adsk.eagle:footprint:44429191/1" library_version="35">
<smd name="16" x="40.62" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="15" x="38.08" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="14" x="35.54" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="13" x="33" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="12" x="30.46" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="11" x="27.92" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="10" x="25.38" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="9" x="22.84" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="8" x="20.3" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="7" x="17.76" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="26" x="66.02" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="25" x="63.48" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="24" x="60.94" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="23" x="58.4" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="22" x="55.86" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="21" x="53.32" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="20" x="50.78" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="19" x="48.24" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="18" x="45.7" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="17" x="43.16" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="30" x="76.18" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="29" x="73.64" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="28" x="71.1" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="1" x="2.52" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="2" x="5.06" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="3" x="7.6" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="4" x="10.14" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="5" x="12.68" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="6" x="15.22" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="27" x="68.56" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="31" x="78.72" y="4.5" dx="8" dy="1.8" layer="1" rot="R90"/>
<smd name="47" x="40.62" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="48" x="38.08" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="49" x="35.54" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="50" x="33" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="51" x="30.46" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="52" x="27.92" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="53" x="25.38" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="54" x="22.84" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="55" x="20.3" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="56" x="17.76" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="37" x="66.02" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="38" x="63.48" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="39" x="60.94" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="40" x="58.4" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="41" x="55.86" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="42" x="53.32" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="43" x="50.78" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="44" x="48.24" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="45" x="45.7" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="46" x="43.16" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="33" x="76.18" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="34" x="73.64" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="35" x="71.1" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="62" x="2.52" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="61" x="5.06" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="60" x="7.6" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="59" x="10.14" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="58" x="12.68" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="57" x="15.22" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="36" x="68.56" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<smd name="32" x="78.72" y="4.5" dx="8" dy="1.8" layer="16" rot="R270"/>
<wire x1="0" y1="0" x2="81.2" y2="0" width="0" layer="20"/>
<wire x1="81.2" y1="0" x2="81.2" y2="10" width="0" layer="20"/>
<wire x1="0" y1="0" x2="0" y2="10" width="0" layer="20"/>
<text x="2" y="10" size="1.27" layer="21">1</text>
<text x="78" y="10" size="1.27" layer="21">31</text>
<text x="80" y="10" size="1.27" layer="22" rot="MR0">32</text>
<text x="4" y="10" size="1.27" layer="22" rot="MR0">62</text>
<text x="5" y="10" size="1.27" layer="25">&gt;NAME</text>
</package>
<package name="DB25G-M" urn="urn:adsk.eagle:footprint:44435034/1" library_version="35" library_locally_modified="yes">
<pad name="7" x="0" y="1.42" drill="1"/>
<pad name="6" x="-2.77" y="1.42" drill="1"/>
<pad name="5" x="-5.54" y="1.42" drill="1"/>
<pad name="4" x="-8.31" y="1.42" drill="1"/>
<pad name="3" x="-11.08" y="1.42" drill="1"/>
<pad name="2" x="-13.85" y="1.42" drill="1"/>
<pad name="1" x="-16.62" y="1.42" drill="1"/>
<pad name="8" x="2.77" y="1.42" drill="1"/>
<pad name="9" x="5.54" y="1.42" drill="1"/>
<pad name="10" x="8.31" y="1.42" drill="1"/>
<pad name="11" x="11.08" y="1.42" drill="1"/>
<pad name="12" x="13.85" y="1.42" drill="1"/>
<pad name="13" x="16.62" y="1.42" drill="1"/>
<pad name="19" x="-1.385" y="-1.42" drill="1"/>
<pad name="18" x="-4.155" y="-1.42" drill="1"/>
<pad name="20" x="1.385" y="-1.42" drill="1"/>
<pad name="17" x="-6.925" y="-1.42" drill="1"/>
<pad name="16" x="-9.695" y="-1.42" drill="1"/>
<pad name="15" x="-12.465" y="-1.42" drill="1"/>
<pad name="14" x="-15.235" y="-1.42" drill="1"/>
<pad name="21" x="4.19" y="-1.385" drill="1" rot="R90"/>
<pad name="22" x="6.925" y="-1.35" drill="1" rot="R180"/>
<pad name="23" x="9.66" y="-1.385" drill="1" rot="R270"/>
<pad name="24" x="12.465" y="-1.42" drill="1"/>
<pad name="25" x="15.27" y="-1.385" drill="1" rot="R90"/>
<pad name="SHIELD1" x="-23.52" y="0" drill="3.2"/>
<pad name="SHIELD2" x="23.52" y="0" drill="3.2"/>
<text x="-23" y="9" size="1.27" layer="25">&gt;NAME</text>
<wire x1="-25" y1="6.275" x2="-26.52" y2="5" width="0.127" layer="21" curve="90"/>
<wire x1="-26.52" y1="5" x2="-26.52" y2="-5" width="0.127" layer="21"/>
<wire x1="-26.52" y1="-5" x2="-25" y2="-6.275" width="0.127" layer="21" curve="90"/>
<wire x1="-25" y1="-6.275" x2="25" y2="-6.275" width="0.127" layer="21"/>
<wire x1="25" y1="-6.275" x2="26.52" y2="-5" width="0.127" layer="21" curve="90"/>
<wire x1="26.52" y1="-5" x2="26.52" y2="5" width="0.127" layer="21"/>
<wire x1="26.52" y1="5" x2="25" y2="6.275" width="0.127" layer="21" curve="90"/>
<wire x1="25" y1="6.275" x2="-25" y2="6.275" width="0.127" layer="21"/>
</package>
<package name="DB25G-F" urn="urn:adsk.eagle:footprint:44435035/1" library_version="35" library_locally_modified="yes">
<pad name="7" x="0" y="1.42" drill="1"/>
<pad name="8" x="-2.77" y="1.42" drill="1"/>
<pad name="9" x="-5.54" y="1.42" drill="1"/>
<pad name="10" x="-8.31" y="1.42" drill="1"/>
<pad name="11" x="-11.08" y="1.42" drill="1"/>
<pad name="12" x="-13.85" y="1.42" drill="1"/>
<pad name="13" x="-16.62" y="1.42" drill="1"/>
<pad name="6" x="2.77" y="1.42" drill="1"/>
<pad name="5" x="5.54" y="1.42" drill="1"/>
<pad name="4" x="8.31" y="1.42" drill="1"/>
<pad name="3" x="11.08" y="1.42" drill="1"/>
<pad name="2" x="13.85" y="1.42" drill="1"/>
<pad name="1" x="16.62" y="1.42" drill="1"/>
<pad name="20" x="-1.385" y="-1.42" drill="1"/>
<pad name="21" x="-4.155" y="-1.42" drill="1"/>
<pad name="19" x="1.385" y="-1.42" drill="1"/>
<pad name="22" x="-6.925" y="-1.42" drill="1"/>
<pad name="23" x="-9.695" y="-1.42" drill="1"/>
<pad name="24" x="-12.465" y="-1.42" drill="1"/>
<pad name="25" x="-15.235" y="-1.42" drill="1"/>
<pad name="18" x="4.19" y="-1.385" drill="1" rot="R90"/>
<pad name="17" x="6.925" y="-1.35" drill="1" rot="R180"/>
<pad name="16" x="9.66" y="-1.385" drill="1" rot="R270"/>
<pad name="15" x="12.465" y="-1.42" drill="1"/>
<pad name="14" x="15.27" y="-1.385" drill="1" rot="R90"/>
<pad name="SHIELD1" x="-23.52" y="0" drill="3.2"/>
<pad name="SHIELD2" x="23.52" y="0" drill="3.2"/>
<text x="-23" y="9" size="1.27" layer="25">&gt;NAME</text>
<wire x1="-25" y1="6.275" x2="-26.52" y2="5" width="0.127" layer="21" curve="90"/>
<wire x1="-26.52" y1="5" x2="-26.52" y2="-5" width="0.127" layer="21"/>
<wire x1="-26.52" y1="-5" x2="-25" y2="-6.275" width="0.127" layer="21" curve="90"/>
<wire x1="-25" y1="-6.275" x2="25" y2="-6.275" width="0.127" layer="21"/>
<wire x1="25" y1="-6.275" x2="26.52" y2="-5" width="0.127" layer="21" curve="90"/>
<wire x1="26.52" y1="-5" x2="26.52" y2="5" width="0.127" layer="21"/>
<wire x1="26.52" y1="5" x2="25" y2="6.275" width="0.127" layer="21" curve="90"/>
<wire x1="25" y1="6.275" x2="-25" y2="6.275" width="0.127" layer="21"/>
</package>
<package name="DS1034-15" urn="urn:adsk.eagle:footprint:44435033/1" library_version="35" library_locally_modified="yes">
<pad name="4" x="-1.385" y="1.42" drill="1"/>
<pad name="3" x="-4.155" y="1.42" drill="1"/>
<pad name="2" x="-6.925" y="1.42" drill="1"/>
<pad name="1" x="-9.695" y="1.42" drill="1"/>
<pad name="5" x="1.385" y="1.42" drill="1"/>
<pad name="6" x="4.155" y="1.42" drill="1"/>
<pad name="7" x="6.925" y="1.42" drill="1"/>
<pad name="8" x="9.695" y="1.42" drill="1"/>
<pad name="12" x="0" y="-1.42" drill="1"/>
<pad name="11" x="-2.77" y="-1.42" drill="1"/>
<pad name="10" x="-5.54" y="-1.42" drill="1"/>
<pad name="9" x="-8.31" y="-1.42" drill="1"/>
<pad name="13" x="2.77" y="-1.42" drill="1"/>
<pad name="14" x="5.54" y="-1.42" drill="1"/>
<pad name="15" x="8.31" y="-1.42" drill="1"/>
<pad name="SHIELD1" x="-16.66" y="0" drill="3.2"/>
<pad name="SHIELD2" x="16.66" y="0" drill="3.2"/>
<wire x1="-18.5" y1="6.25" x2="-19.57" y2="5.08" width="0.127" layer="21" curve="90"/>
<wire x1="-19.57" y1="5.08" x2="-19.57" y2="-5.08" width="0.127" layer="21"/>
<wire x1="-19.57" y1="-5.08" x2="-18.5" y2="-6.25" width="0.127" layer="21" curve="90"/>
<wire x1="-18.5" y1="-6.25" x2="18.5" y2="-6.25" width="0.127" layer="21"/>
<wire x1="18.5" y1="-6.25" x2="19.57" y2="-5.08" width="0.127" layer="21" curve="90"/>
<wire x1="19.57" y1="-5.08" x2="19.57" y2="5.08" width="0.127" layer="21"/>
<wire x1="19.57" y1="5.08" x2="18.5" y2="6.25" width="0.127" layer="21" curve="90"/>
<wire x1="18.5" y1="6.25" x2="-18.5" y2="6.25" width="0.127" layer="21"/>
<text x="-17.78" y="8.89" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="DB9G-F" urn="urn:adsk.eagle:footprint:44435036/1" library_version="35" library_locally_modified="yes">
<pad name="3" x="0" y="1.42" drill="1"/>
<pad name="4" x="-2.77" y="1.42" drill="1"/>
<pad name="5" x="-5.54" y="1.42" drill="1"/>
<pad name="2" x="2.77" y="1.42" drill="1"/>
<pad name="1" x="5.54" y="1.42" drill="1"/>
<pad name="7" x="1.385" y="-1.42" drill="1"/>
<pad name="6" x="4.155" y="-1.42" drill="1"/>
<pad name="8" x="-1.385" y="-1.42" drill="1"/>
<pad name="9" x="-4.155" y="-1.42" drill="1"/>
<pad name="SHIELD1" x="-12.495" y="0" drill="3.2"/>
<pad name="SHIELD2" x="12.495" y="0" drill="3.2"/>
<wire x1="-14.5" y1="6.25" x2="-15.4" y2="5" width="0.127" layer="21" curve="90"/>
<wire x1="-15.4" y1="5" x2="-15.4" y2="-5" width="0.127" layer="21"/>
<wire x1="-15.4" y1="-5" x2="-14.5" y2="-6.25" width="0.127" layer="21" curve="90"/>
<wire x1="-14.5" y1="-6.25" x2="14.5" y2="-6.25" width="0.127" layer="21"/>
<wire x1="14.5" y1="-6.25" x2="15.4" y2="-5" width="0.127" layer="21" curve="90"/>
<wire x1="15.4" y1="-5" x2="15.4" y2="5" width="0.127" layer="21"/>
<wire x1="15.4" y1="5" x2="14.5" y2="6.25" width="0.127" layer="21" curve="90"/>
<wire x1="14.5" y1="6.25" x2="-14.5" y2="6.25" width="0.127" layer="21"/>
<text x="-14" y="8" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="PH-7MP" urn="urn:adsk.eagle:footprint:44435037/1" locally_modified="yes" library_version="35" library_locally_modified="yes">
<pad name="7" x="0" y="0" drill="1.8"/>
<wire x1="0" y1="7.25" x2="-7.25" y2="0" width="0.127" layer="21" curve="90"/>
<wire x1="-7.25" y1="0" x2="0" y2="-7.25" width="0.127" layer="21" curve="90"/>
<wire x1="0" y1="-7.25" x2="7.25" y2="0" width="0.127" layer="21" curve="90"/>
<wire x1="7.25" y1="0" x2="0" y2="7.25" width="0.127" layer="21" curve="90"/>
<pad name="1" x="3.7" y="0" drill="1.8"/>
<pad name="2" x="2.32890625" y="-2.876634375" drill="1.8"/>
<pad name="3" x="-0.769509375" y="-3.62141875" drill="1.8"/>
<pad name="4" x="-3.29821875" y="-1.682203125" drill="1.8"/>
<pad name="5" x="-3.38253125" y="1.50335625" drill="1.8"/>
<pad name="6" x="-0.95994375" y="3.57361875" drill="1.8"/>
<wire x1="0" y1="8.8" x2="-8.8" y2="0" width="0.127" layer="21" curve="90"/>
<wire x1="-8.8" y1="0" x2="0" y2="-8.8" width="0.127" layer="21" curve="90"/>
<wire x1="0" y1="-8.8" x2="8.8" y2="0" width="0.127" layer="21" curve="90"/>
<wire x1="8.8" y1="0" x2="0" y2="8.8" width="0.127" layer="21" curve="90"/>
<text x="-6" y="10" size="1.27" layer="21">&gt;NAME</text>
</package>
<package name="MF3.0_1X4MR" urn="urn:adsk.eagle:footprint:31813526/2" library_version="35" library_locally_modified="yes">
<pad name="4" x="-4.5" y="0" drill="1"/>
<pad name="3" x="-1.5" y="0" drill="1"/>
<pad name="2" x="1.5" y="0" drill="1"/>
<pad name="1" x="4.5" y="0" drill="1"/>
<hole x="-2.35" y="-4.3" drill="3"/>
<hole x="2.35" y="-4.3" drill="3"/>
<wire x1="-7.82" y1="1" x2="-7.82" y2="-7.5" width="0.127" layer="21"/>
<wire x1="-7.82" y1="-7.5" x2="-6.42" y2="-8.9" width="0.127" layer="21"/>
<wire x1="-6.42" y1="-8.9" x2="6.42" y2="-8.9" width="0.127" layer="21"/>
<wire x1="6.42" y1="-8.9" x2="7.82" y2="-7.5" width="0.127" layer="21"/>
<wire x1="7.82" y1="-7.5" x2="7.82" y2="1" width="0.127" layer="21"/>
<wire x1="7.82" y1="1" x2="-7.82" y2="1" width="0.127" layer="21"/>
<wire x1="-9.3" y1="-14.46" x2="9.3" y2="-14.46" width="0" layer="48"/>
<wire x1="-1.5" y1="-8" x2="1.5" y2="-8" width="0.127" layer="51"/>
<wire x1="1.5" y1="-8" x2="1.5" y2="-6.4" width="0.127" layer="51"/>
<wire x1="1.5" y1="-6.4" x2="1.5" y2="-6" width="0.127" layer="51"/>
<wire x1="1.5" y1="-6" x2="-1.5" y2="-6" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-6" x2="-1.5" y2="-6.4" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-6.4" x2="-1.5" y2="-8" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-6.4" x2="1.5" y2="-6.4" width="0.127" layer="51"/>
<wire x1="6" y1="-1.5" x2="5.5" y2="-2.5" width="0.127" layer="21"/>
<wire x1="5.5" y1="-2.5" x2="6.5" y2="-2.5" width="0.127" layer="21"/>
<wire x1="6.5" y1="-2.5" x2="6" y2="-1.5" width="0.127" layer="21"/>
<text x="0" y="-14" size="1.27" layer="48" align="bottom-center">MAX </text>
<text x="-2.54" y="2.54" size="1.27" layer="25">&gt;NAME</text>
</package>
<package name="MF3.0_1X3MR" urn="urn:adsk.eagle:footprint:31813524/2" library_version="35" library_locally_modified="yes">
<pad name="3" x="-3" y="0" drill="1"/>
<pad name="2" x="0" y="0" drill="1"/>
<pad name="1" x="3" y="0" drill="1"/>
<hole x="0" y="-4.3" drill="3"/>
<wire x1="-6.32" y1="1" x2="-6.32" y2="-7.5" width="0.127" layer="21"/>
<wire x1="-6.32" y1="-7.5" x2="-4.92" y2="-8.9" width="0.127" layer="21"/>
<wire x1="-4.92" y1="-8.9" x2="4.92" y2="-8.9" width="0.127" layer="21"/>
<wire x1="4.92" y1="-8.9" x2="6.32" y2="-7.5" width="0.127" layer="21"/>
<wire x1="6.32" y1="-7.5" x2="6.32" y2="1" width="0.127" layer="21"/>
<wire x1="6.32" y1="1" x2="-6.32" y2="1" width="0.127" layer="21"/>
<wire x1="-9.3" y1="-14.46" x2="9.3" y2="-14.46" width="0" layer="48"/>
<wire x1="-1.5" y1="-8" x2="1.5" y2="-8" width="0.127" layer="51"/>
<wire x1="1.5" y1="-8" x2="1.5" y2="-6.4" width="0.127" layer="51"/>
<wire x1="1.5" y1="-6.4" x2="1.5" y2="-6" width="0.127" layer="51"/>
<wire x1="1.5" y1="-6" x2="-1.5" y2="-6" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-6" x2="-1.5" y2="-6.4" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-6.4" x2="-1.5" y2="-8" width="0.127" layer="51"/>
<wire x1="-1.5" y1="-6.4" x2="1.5" y2="-6.4" width="0.127" layer="51"/>
<wire x1="4" y1="-2.5" x2="5" y2="-2.5" width="0.127" layer="21"/>
<wire x1="5" y1="-2.5" x2="4.5" y2="-1.5" width="0.127" layer="21"/>
<wire x1="4.5" y1="-1.5" x2="4" y2="-2.5" width="0.127" layer="21"/>
<text x="0" y="-14" size="1.27" layer="48" align="bottom-center">MAX </text>
<text x="-2.54" y="2.54" size="1.27" layer="25">&gt;NAME</text>
</package>
<package name="MF3.0_1X4MV" library_version="35" library_locally_modified="yes">
<pad name="4" x="-4.5" y="0" drill="1"/>
<pad name="3" x="-1.5" y="0" drill="1"/>
<pad name="2" x="1.5" y="0" drill="1"/>
<pad name="1" x="4.5" y="0" drill="1"/>
<wire x1="5.5" y1="-1" x2="5" y2="-2" width="0.127" layer="21"/>
<wire x1="5" y1="-2" x2="6" y2="-2" width="0.127" layer="21"/>
<wire x1="6" y1="-2" x2="5.5" y2="-1" width="0.127" layer="21"/>
<text x="-5.54" y="3.54" size="1.27" layer="25">&gt;NAME</text>
<wire x1="-6.45" y1="2.625" x2="6.45" y2="2.625" width="0.127" layer="21"/>
<wire x1="-6.45" y1="2.625" x2="-6.45" y2="-2.625" width="0.127" layer="21"/>
<wire x1="-6.45" y1="-2.625" x2="6.45" y2="-2.625" width="0.127" layer="21"/>
<wire x1="6.55" y1="2.625" x2="6.55" y2="-2.625" width="0.127" layer="21"/>
</package>
<package name="MF3.0_1X3MV" library_version="35" library_locally_modified="yes">
<pad name="3" x="-3" y="0" drill="1"/>
<pad name="2" x="0" y="0" drill="1"/>
<pad name="1" x="3" y="0" drill="1"/>
<wire x1="3.5" y1="-2" x2="4.5" y2="-2" width="0.127" layer="21"/>
<wire x1="4.5" y1="-2" x2="4" y2="-1" width="0.127" layer="21"/>
<wire x1="4" y1="-1" x2="3.5" y2="-2" width="0.127" layer="21"/>
<text x="-4.54" y="3.54" size="1.27" layer="25">&gt;NAME</text>
<wire x1="-5" y1="2.625" x2="5" y2="2.625" width="0.127" layer="21"/>
<wire x1="-5" y1="-2.625" x2="5" y2="-2.625" width="0.127" layer="21"/>
<wire x1="-5" y1="-2.625" x2="-5" y2="2.625" width="0.127" layer="21"/>
<wire x1="5" y1="-2.625" x2="5" y2="2.625" width="0.127" layer="21"/>
</package>
</packages>
<packages3d>
<package3d name="KLS1-603C-SMT" urn="urn:adsk.eagle:package:42556913/3" type="model" library_version="35">
<packageinstances>
<packageinstance name="KLS1-603C-SMT"/>
</packageinstances>
</package3d>
<package3d name="KLS1-603C-SLOT" urn="urn:adsk.eagle:package:44429192/2" type="empty" library_version="35">
<packageinstances>
<packageinstance name="KLS1-603C-SLOT"/>
</packageinstances>
</package3d>
<package3d name="DB25G-M" urn="urn:adsk.eagle:package:44435039/1" type="box" library_version="35" library_locally_modified="yes">
<packageinstances>
<packageinstance name="DB25G-M"/>
</packageinstances>
</package3d>
<package3d name="DB25G-F" urn="urn:adsk.eagle:package:44435040/1" type="box" library_version="35" library_locally_modified="yes">
<packageinstances>
<packageinstance name="DB25G-F"/>
</packageinstances>
</package3d>
<package3d name="DS1034-15" urn="urn:adsk.eagle:package:44435038/1" type="box" library_version="35" library_locally_modified="yes">
<packageinstances>
<packageinstance name="DS1034-15"/>
</packageinstances>
</package3d>
<package3d name="DB9G-F" urn="urn:adsk.eagle:package:44435041/1" type="box" library_version="35" library_locally_modified="yes">
<packageinstances>
<packageinstance name="DB9G-F"/>
</packageinstances>
</package3d>
<package3d name="PH-7MP" urn="urn:adsk.eagle:package:44435042/1" type="box" library_version="35" library_locally_modified="yes">
<packageinstances>
<packageinstance name="PH-7MP"/>
</packageinstances>
</package3d>
<package3d name="MF3.0_1X4MR" urn="urn:adsk.eagle:package:31813567/2" type="box" library_version="35" library_locally_modified="yes">
<packageinstances>
<packageinstance name="MF3.0_1X4MR"/>
</packageinstances>
</package3d>
<package3d name="MF3.0_1X3MR" urn="urn:adsk.eagle:package:31813569/2" type="box" library_version="35" library_locally_modified="yes">
<packageinstances>
<packageinstance name="MF3.0_1X3MR"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PIN-15" urn="urn:adsk.eagle:symbol:31813456/2" library_version="35">
<pin name="1" x="-7.62" y="17.78" length="middle"/>
<pin name="2" x="-7.62" y="15.24" length="middle"/>
<pin name="3" x="-7.62" y="12.7" length="middle"/>
<pin name="4" x="-7.62" y="10.16" length="middle"/>
<pin name="5" x="-7.62" y="7.62" length="middle"/>
<pin name="6" x="-7.62" y="5.08" length="middle"/>
<pin name="7" x="-7.62" y="2.54" length="middle"/>
<pin name="8" x="-7.62" y="0" length="middle"/>
<pin name="9" x="-7.62" y="-2.54" length="middle"/>
<pin name="10" x="-7.62" y="-5.08" length="middle"/>
<pin name="11" x="-7.62" y="-7.62" length="middle"/>
<pin name="12" x="-7.62" y="-10.16" length="middle"/>
<pin name="13" x="-7.62" y="-12.7" length="middle"/>
<pin name="14" x="-7.62" y="-15.24" length="middle"/>
<pin name="15" x="-7.62" y="-17.78" length="middle"/>
<wire x1="-2.54" y1="20.32" x2="2.54" y2="20.32" width="0.254" layer="94"/>
<wire x1="2.54" y1="20.32" x2="2.54" y2="-20.32" width="0.254" layer="94"/>
<wire x1="2.54" y1="-20.32" x2="-2.54" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-20.32" x2="-2.54" y2="20.32" width="0.254" layer="94"/>
<text x="-2.54" y="22.86" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-25.4" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="PIN-16" urn="urn:adsk.eagle:symbol:31813455/2" library_version="35">
<pin name="1" x="-7.62" y="17.78" length="middle"/>
<pin name="2" x="-7.62" y="15.24" length="middle"/>
<pin name="3" x="-7.62" y="12.7" length="middle"/>
<pin name="4" x="-7.62" y="10.16" length="middle"/>
<pin name="5" x="-7.62" y="7.62" length="middle"/>
<pin name="6" x="-7.62" y="5.08" length="middle"/>
<pin name="7" x="-7.62" y="2.54" length="middle"/>
<pin name="8" x="-7.62" y="0" length="middle"/>
<pin name="9" x="-7.62" y="-2.54" length="middle"/>
<pin name="10" x="-7.62" y="-5.08" length="middle"/>
<pin name="11" x="-7.62" y="-7.62" length="middle"/>
<pin name="12" x="-7.62" y="-10.16" length="middle"/>
<pin name="13" x="-7.62" y="-12.7" length="middle"/>
<pin name="14" x="-7.62" y="-15.24" length="middle"/>
<pin name="15" x="-7.62" y="-17.78" length="middle"/>
<pin name="16" x="-7.62" y="-20.32" length="middle"/>
<wire x1="-2.54" y1="20.32" x2="2.54" y2="20.32" width="0.254" layer="94"/>
<wire x1="2.54" y1="20.32" x2="2.54" y2="-22.86" width="0.254" layer="94"/>
<wire x1="2.54" y1="-22.86" x2="-2.54" y2="-22.86" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-22.86" x2="-2.54" y2="20.32" width="0.254" layer="94"/>
<text x="-2.54" y="22.86" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-27.94" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="F25G" urn="urn:adsk.eagle:symbol:31813493/2" library_version="35" library_locally_modified="yes">
<wire x1="-1.651" y1="16.129" x2="-1.651" y2="14.351" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="14.351" x2="1.524" y2="16.129" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="13.589" x2="-1.651" y2="11.811" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="11.811" x2="1.524" y2="13.589" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="11.049" x2="-1.651" y2="9.271" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="9.271" x2="1.524" y2="11.049" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="8.509" x2="-1.651" y2="6.731" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="6.731" x2="1.524" y2="8.509" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="5.969" x2="-1.651" y2="4.191" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="4.191" x2="1.524" y2="5.969" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="3.429" x2="-1.651" y2="1.651" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="1.651" x2="1.524" y2="3.429" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="0.889" x2="-1.651" y2="-0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-0.889" x2="1.524" y2="0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-1.651" x2="-1.651" y2="-3.429" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-3.429" x2="1.524" y2="-1.651" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-4.191" x2="-1.651" y2="-5.969" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-5.969" x2="1.524" y2="-4.191" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-6.731" x2="-1.651" y2="-8.509" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-8.509" x2="1.524" y2="-6.731" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-9.271" x2="-1.651" y2="-11.049" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-11.049" x2="1.524" y2="-9.271" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-11.811" x2="-1.651" y2="-13.589" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-13.589" x2="1.524" y2="-11.811" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-14.351" x2="-1.651" y2="-16.129" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-4.064" y1="17.0912" x2="-2.5226" y2="18.332" width="0.4064" layer="94" curve="-102.324066" cap="flat"/>
<wire x1="-2.5226" y1="18.3318" x2="0" y2="17.78" width="0.4064" layer="94"/>
<wire x1="0" y1="17.78" x2="3.0654" y2="17.1094" width="0.4064" layer="94"/>
<wire x1="3.0654" y1="17.1095" x2="4.0642" y2="15.8688" width="0.4064" layer="94" curve="-77.655139" cap="flat"/>
<wire x1="4.064" y1="-15.8688" x2="4.064" y2="15.8688" width="0.4064" layer="94"/>
<wire x1="3.0654" y1="-17.1094" x2="4.064" y2="-15.8688" width="0.4064" layer="94" curve="77.657889"/>
<wire x1="-4.064" y1="-17.0912" x2="-4.064" y2="17.0912" width="0.4064" layer="94"/>
<wire x1="-2.5226" y1="-18.3318" x2="0" y2="-17.78" width="0.4064" layer="94"/>
<wire x1="0" y1="-17.78" x2="3.0654" y2="-17.1094" width="0.4064" layer="94"/>
<wire x1="-4.064" y1="-17.0912" x2="-2.5226" y2="-18.3319" width="0.4064" layer="94" curve="102.337599" cap="flat"/>
<wire x1="2.54" y1="17.78" x2="0" y2="17.78" width="0.1524" layer="94"/>
<wire x1="0" y1="-17.78" x2="2.54" y2="-17.78" width="0.1524" layer="94"/>
<circle x="0" y="17.78" radius="0.254" width="0.6096" layer="94"/>
<circle x="0" y="-17.78" radius="0.254" width="0.6096" layer="94"/>
<text x="-3.81" y="-20.955" size="1.778" layer="96">&gt;VALUE</text>
<text x="-3.81" y="19.05" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="-7.62" y="15.24" visible="pad" length="middle" direction="pas"/>
<pin name="14" x="7.62" y="15.24" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="2" x="-7.62" y="12.7" visible="pad" length="middle" direction="pas"/>
<pin name="15" x="7.62" y="12.7" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="3" x="-7.62" y="10.16" visible="pad" length="middle" direction="pas"/>
<pin name="16" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="4" x="-7.62" y="7.62" visible="pad" length="middle" direction="pas"/>
<pin name="17" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="5" x="-7.62" y="5.08" visible="pad" length="middle" direction="pas"/>
<pin name="18" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="6" x="-7.62" y="2.54" visible="pad" length="middle" direction="pas"/>
<pin name="19" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="7" x="-7.62" y="0" visible="pad" length="middle" direction="pas"/>
<pin name="20" x="7.62" y="0" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="8" x="-7.62" y="-2.54" visible="pad" length="middle" direction="pas"/>
<pin name="21" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="9" x="-7.62" y="-5.08" visible="pad" length="middle" direction="pas"/>
<pin name="22" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="10" x="-7.62" y="-7.62" visible="pad" length="middle" direction="pas"/>
<pin name="23" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="11" x="-7.62" y="-10.16" visible="pad" length="middle" direction="pas"/>
<pin name="24" x="7.62" y="-10.16" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="12" x="-7.62" y="-12.7" visible="pad" length="middle" direction="pas"/>
<pin name="25" x="7.62" y="-12.7" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="13" x="-7.62" y="-15.24" visible="pad" length="middle" direction="pas"/>
<pin name="G1" x="7.62" y="17.78" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="G2" x="7.62" y="-17.78" visible="pad" length="middle" direction="pas" rot="R180"/>
</symbol>
<symbol name="F15G" urn="urn:adsk.eagle:symbol:31813492/2" library_version="35" library_locally_modified="yes">
<wire x1="-1.651" y1="8.509" x2="-1.651" y2="6.731" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="6.731" x2="1.524" y2="8.509" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="5.969" x2="-1.651" y2="4.191" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="4.191" x2="1.524" y2="5.969" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="3.429" x2="-1.651" y2="1.651" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="1.651" x2="1.524" y2="3.429" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="0.889" x2="-1.651" y2="-0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-0.889" x2="1.524" y2="0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-1.651" x2="-1.651" y2="-3.429" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-3.429" x2="1.524" y2="-1.651" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-4.191" x2="-1.651" y2="-5.969" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-5.969" x2="1.524" y2="-4.191" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-6.731" x2="-1.651" y2="-8.509" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-8.509" x2="1.524" y2="-6.731" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-9.271" x2="-1.651" y2="-11.049" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-4.064" y1="9.4712" x2="-2.5226" y2="10.712" width="0.4064" layer="94" curve="-102.324066" cap="flat"/>
<wire x1="-2.5226" y1="10.7118" x2="0" y2="10.16" width="0.4064" layer="94"/>
<wire x1="0" y1="10.16" x2="3.0654" y2="9.4894" width="0.4064" layer="94"/>
<wire x1="3.0654" y1="9.4895" x2="4.0642" y2="8.2488" width="0.4064" layer="94" curve="-77.655139" cap="flat"/>
<wire x1="4.064" y1="-10.7888" x2="4.064" y2="8.2488" width="0.4064" layer="94"/>
<wire x1="3.0654" y1="-12.0294" x2="4.064" y2="-10.7888" width="0.4064" layer="94" curve="77.657889"/>
<wire x1="-4.064" y1="-12.0112" x2="-4.064" y2="9.4712" width="0.4064" layer="94"/>
<wire x1="-2.5226" y1="-13.2518" x2="0" y2="-12.7" width="0.4064" layer="94"/>
<wire x1="0" y1="-12.7" x2="3.0654" y2="-12.0294" width="0.4064" layer="94"/>
<wire x1="-4.064" y1="-12.0112" x2="-2.5226" y2="-13.2519" width="0.4064" layer="94" curve="102.337599" cap="flat"/>
<wire x1="2.54" y1="10.16" x2="0" y2="10.16" width="0.1524" layer="94"/>
<wire x1="0" y1="-12.7" x2="2.54" y2="-12.7" width="0.1524" layer="94"/>
<circle x="0" y="10.16" radius="0.254" width="0.6096" layer="94"/>
<circle x="0" y="-12.7" radius="0.254" width="0.6096" layer="94"/>
<text x="-4.445" y="-15.875" size="1.778" layer="96">&gt;VALUE</text>
<text x="-3.81" y="11.43" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="-7.62" y="7.62" visible="pad" length="middle" direction="pas"/>
<pin name="2" x="-7.62" y="5.08" visible="pad" length="middle" direction="pas"/>
<pin name="3" x="-7.62" y="2.54" visible="pad" length="middle" direction="pas"/>
<pin name="4" x="-7.62" y="0" visible="pad" length="middle" direction="pas"/>
<pin name="5" x="-7.62" y="-2.54" visible="pad" length="middle" direction="pas"/>
<pin name="6" x="-7.62" y="-5.08" visible="pad" length="middle" direction="pas"/>
<pin name="7" x="-7.62" y="-7.62" visible="pad" length="middle" direction="pas"/>
<pin name="8" x="-7.62" y="-10.16" visible="pad" length="middle" direction="pas"/>
<pin name="9" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="10" x="7.62" y="5.08" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="11" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="12" x="7.62" y="0" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="13" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="14" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="15" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="G1" x="7.62" y="10.16" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="G2" x="7.62" y="-12.7" visible="pad" length="middle" direction="pas" rot="R180"/>
</symbol>
<symbol name="F09G" urn="urn:adsk.eagle:symbol:31813491/2" library_version="35" library_locally_modified="yes">
<wire x1="-1.651" y1="3.429" x2="-1.651" y2="1.651" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="1.651" x2="1.524" y2="3.429" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="5.969" x2="-1.651" y2="4.191" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-3.429" x2="1.524" y2="-1.651" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="0.889" x2="-1.651" y2="-0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-0.889" x2="1.524" y2="0.889" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-1.651" x2="-1.651" y2="-3.429" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="1.524" y1="-5.969" x2="1.524" y2="-4.191" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-1.651" y1="-4.191" x2="-1.651" y2="-5.969" width="0.254" layer="94" curve="180" cap="flat"/>
<wire x1="-4.064" y1="6.9312" x2="-2.5226" y2="8.172" width="0.4064" layer="94" curve="-102.324066" cap="flat"/>
<wire x1="-2.5226" y1="8.1718" x2="0" y2="7.62" width="0.4064" layer="94"/>
<wire x1="0" y1="7.62" x2="3.0654" y2="6.9494" width="0.4064" layer="94"/>
<wire x1="3.0654" y1="6.9495" x2="4.0642" y2="5.7088" width="0.4064" layer="94" curve="-77.655139" cap="flat"/>
<wire x1="4.064" y1="-5.7088" x2="4.064" y2="5.7088" width="0.4064" layer="94"/>
<wire x1="3.0654" y1="-6.9494" x2="4.064" y2="-5.7088" width="0.4064" layer="94" curve="77.657889"/>
<wire x1="-4.064" y1="-6.9312" x2="-4.064" y2="6.9312" width="0.4064" layer="94"/>
<wire x1="-2.5226" y1="-8.1718" x2="0" y2="-7.62" width="0.4064" layer="94"/>
<wire x1="0" y1="-7.62" x2="3.0654" y2="-6.9494" width="0.4064" layer="94"/>
<wire x1="-4.064" y1="-6.9312" x2="-2.5226" y2="-8.1719" width="0.4064" layer="94" curve="102.337599" cap="flat"/>
<wire x1="2.54" y1="7.62" x2="0" y2="7.62" width="0.1524" layer="94"/>
<wire x1="0" y1="-7.62" x2="2.54" y2="-7.62" width="0.1524" layer="94"/>
<circle x="0" y="7.62" radius="0.254" width="0.6096" layer="94"/>
<circle x="0" y="-7.62" radius="0.254" width="0.6096" layer="94"/>
<text x="-3.81" y="-10.795" size="1.778" layer="96">&gt;VALUE</text>
<text x="-3.81" y="8.89" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="-7.62" y="5.08" visible="pad" length="middle" direction="pas"/>
<pin name="6" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="2" x="-7.62" y="2.54" visible="pad" length="middle" direction="pas"/>
<pin name="7" x="7.62" y="0" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="3" x="-7.62" y="0" visible="pad" length="middle" direction="pas"/>
<pin name="8" x="7.62" y="-2.54" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="4" x="-7.62" y="-2.54" visible="pad" length="middle" direction="pas"/>
<pin name="9" x="7.62" y="-5.08" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="5" x="-7.62" y="-5.08" visible="pad" length="middle" direction="pas"/>
<pin name="G1" x="7.62" y="7.62" visible="pad" length="middle" direction="pas" rot="R180"/>
<pin name="G2" x="7.62" y="-7.62" visible="pad" length="middle" direction="pas" rot="R180"/>
</symbol>
<symbol name="PIN-7" urn="urn:adsk.eagle:symbol:31813464/2" library_version="35" library_locally_modified="yes">
<pin name="1" x="-7.62" y="7.62" length="middle"/>
<pin name="2" x="-7.62" y="5.08" length="middle"/>
<pin name="3" x="-7.62" y="2.54" length="middle"/>
<pin name="4" x="-7.62" y="0" length="middle"/>
<pin name="5" x="-7.62" y="-2.54" length="middle"/>
<pin name="6" x="-7.62" y="-5.08" length="middle"/>
<pin name="7" x="-7.62" y="-7.62" length="middle"/>
<wire x1="-2.54" y1="10.16" x2="2.54" y2="10.16" width="0.254" layer="94"/>
<wire x1="2.54" y1="10.16" x2="2.54" y2="-10.16" width="0.254" layer="94"/>
<wire x1="2.54" y1="-10.16" x2="-2.54" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-10.16" x2="-2.54" y2="10.16" width="0.254" layer="94"/>
<text x="-2.54" y="12.7" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-15.24" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="PIN-4" urn="urn:adsk.eagle:symbol:31813473/2" library_version="35" library_locally_modified="yes">
<pin name="1" x="-7.62" y="5.08" length="middle"/>
<pin name="2" x="-7.62" y="2.54" length="middle"/>
<pin name="3" x="-7.62" y="0" length="middle"/>
<pin name="4" x="-7.62" y="-2.54" length="middle"/>
<wire x1="-2.54" y1="7.62" x2="2.54" y2="7.62" width="0.254" layer="94"/>
<wire x1="2.54" y1="7.62" x2="2.54" y2="-5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="-5.08" x2="-2.54" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-2.54" y2="7.62" width="0.254" layer="94"/>
<text x="-2.54" y="10.16" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="PIN-3" urn="urn:adsk.eagle:symbol:31813468/2" library_version="35" library_locally_modified="yes">
<pin name="1" x="-7.62" y="2.54" length="middle"/>
<pin name="2" x="-7.62" y="0" length="middle"/>
<pin name="3" x="-7.62" y="-2.54" length="middle"/>
<wire x1="-2.54" y1="5.08" x2="2.54" y2="5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="-5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="-5.08" x2="-2.54" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-2.54" y2="5.08" width="0.254" layer="94"/>
<text x="-2.54" y="7.62" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-10.16" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="KLS1-603C" urn="urn:adsk.eagle:component:42556915/5" prefix="J" library_version="35">
<gates>
<gate name="G$1" symbol="PIN-15" x="-35.56" y="38.1"/>
<gate name="G$2" symbol="PIN-16" x="-35.56" y="-5.08"/>
<gate name="G$3" symbol="PIN-15" x="-10.16" y="38.1"/>
<gate name="G$4" symbol="PIN-16" x="-10.16" y="-5.08"/>
</gates>
<devices>
<device name="-SMT" package="KLS1-603C-SMT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$2" pin="1" pad="16"/>
<connect gate="G$2" pin="10" pad="25"/>
<connect gate="G$2" pin="11" pad="26"/>
<connect gate="G$2" pin="12" pad="27"/>
<connect gate="G$2" pin="13" pad="28"/>
<connect gate="G$2" pin="14" pad="29"/>
<connect gate="G$2" pin="15" pad="30"/>
<connect gate="G$2" pin="16" pad="31"/>
<connect gate="G$2" pin="2" pad="17"/>
<connect gate="G$2" pin="3" pad="18"/>
<connect gate="G$2" pin="4" pad="19"/>
<connect gate="G$2" pin="5" pad="20"/>
<connect gate="G$2" pin="6" pad="21"/>
<connect gate="G$2" pin="7" pad="22"/>
<connect gate="G$2" pin="8" pad="23"/>
<connect gate="G$2" pin="9" pad="24"/>
<connect gate="G$3" pin="1" pad="62"/>
<connect gate="G$3" pin="10" pad="53"/>
<connect gate="G$3" pin="11" pad="52"/>
<connect gate="G$3" pin="12" pad="51"/>
<connect gate="G$3" pin="13" pad="50"/>
<connect gate="G$3" pin="14" pad="49"/>
<connect gate="G$3" pin="15" pad="48"/>
<connect gate="G$3" pin="2" pad="61"/>
<connect gate="G$3" pin="3" pad="60"/>
<connect gate="G$3" pin="4" pad="59"/>
<connect gate="G$3" pin="5" pad="58"/>
<connect gate="G$3" pin="6" pad="57"/>
<connect gate="G$3" pin="7" pad="56"/>
<connect gate="G$3" pin="8" pad="55"/>
<connect gate="G$3" pin="9" pad="54"/>
<connect gate="G$4" pin="1" pad="47"/>
<connect gate="G$4" pin="10" pad="38"/>
<connect gate="G$4" pin="11" pad="37"/>
<connect gate="G$4" pin="12" pad="36"/>
<connect gate="G$4" pin="13" pad="35"/>
<connect gate="G$4" pin="14" pad="34"/>
<connect gate="G$4" pin="15" pad="33"/>
<connect gate="G$4" pin="16" pad="32"/>
<connect gate="G$4" pin="2" pad="46"/>
<connect gate="G$4" pin="3" pad="45"/>
<connect gate="G$4" pin="4" pad="44"/>
<connect gate="G$4" pin="5" pad="43"/>
<connect gate="G$4" pin="6" pad="42"/>
<connect gate="G$4" pin="7" pad="41"/>
<connect gate="G$4" pin="8" pad="40"/>
<connect gate="G$4" pin="9" pad="39"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:42556913/3"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SLOT" package="KLS1-603C-SLOT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$2" pin="1" pad="16"/>
<connect gate="G$2" pin="10" pad="25"/>
<connect gate="G$2" pin="11" pad="26"/>
<connect gate="G$2" pin="12" pad="27"/>
<connect gate="G$2" pin="13" pad="28"/>
<connect gate="G$2" pin="14" pad="29"/>
<connect gate="G$2" pin="15" pad="30"/>
<connect gate="G$2" pin="16" pad="31"/>
<connect gate="G$2" pin="2" pad="17"/>
<connect gate="G$2" pin="3" pad="18"/>
<connect gate="G$2" pin="4" pad="19"/>
<connect gate="G$2" pin="5" pad="20"/>
<connect gate="G$2" pin="6" pad="21"/>
<connect gate="G$2" pin="7" pad="22"/>
<connect gate="G$2" pin="8" pad="23"/>
<connect gate="G$2" pin="9" pad="24"/>
<connect gate="G$3" pin="1" pad="62"/>
<connect gate="G$3" pin="10" pad="53"/>
<connect gate="G$3" pin="11" pad="52"/>
<connect gate="G$3" pin="12" pad="51"/>
<connect gate="G$3" pin="13" pad="50"/>
<connect gate="G$3" pin="14" pad="49"/>
<connect gate="G$3" pin="15" pad="48"/>
<connect gate="G$3" pin="2" pad="61"/>
<connect gate="G$3" pin="3" pad="60"/>
<connect gate="G$3" pin="4" pad="59"/>
<connect gate="G$3" pin="5" pad="58"/>
<connect gate="G$3" pin="6" pad="57"/>
<connect gate="G$3" pin="7" pad="56"/>
<connect gate="G$3" pin="8" pad="55"/>
<connect gate="G$3" pin="9" pad="54"/>
<connect gate="G$4" pin="1" pad="47"/>
<connect gate="G$4" pin="10" pad="38"/>
<connect gate="G$4" pin="11" pad="37"/>
<connect gate="G$4" pin="12" pad="36"/>
<connect gate="G$4" pin="13" pad="35"/>
<connect gate="G$4" pin="14" pad="34"/>
<connect gate="G$4" pin="15" pad="33"/>
<connect gate="G$4" pin="16" pad="32"/>
<connect gate="G$4" pin="2" pad="46"/>
<connect gate="G$4" pin="3" pad="45"/>
<connect gate="G$4" pin="4" pad="44"/>
<connect gate="G$4" pin="5" pad="43"/>
<connect gate="G$4" pin="6" pad="42"/>
<connect gate="G$4" pin="7" pad="41"/>
<connect gate="G$4" pin="8" pad="40"/>
<connect gate="G$4" pin="9" pad="39"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:44429192/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DB25G" urn="urn:adsk.eagle:component:44435044/1" prefix="J" library_version="35" library_locally_modified="yes">
<gates>
<gate name="G$1" symbol="F25G" x="0" y="0"/>
</gates>
<devices>
<device name="-VM" package="DB25G-M">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="21" pad="21"/>
<connect gate="G$1" pin="22" pad="22"/>
<connect gate="G$1" pin="23" pad="23"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="25" pad="25"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$1" pin="G1" pad="SHIELD1"/>
<connect gate="G$1" pin="G2" pad="SHIELD2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:44435039/1"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="-VF" package="DB25G-F">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="16" pad="16"/>
<connect gate="G$1" pin="17" pad="17"/>
<connect gate="G$1" pin="18" pad="18"/>
<connect gate="G$1" pin="19" pad="19"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="20" pad="20"/>
<connect gate="G$1" pin="21" pad="21"/>
<connect gate="G$1" pin="22" pad="22"/>
<connect gate="G$1" pin="23" pad="23"/>
<connect gate="G$1" pin="24" pad="24"/>
<connect gate="G$1" pin="25" pad="25"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$1" pin="G1" pad="SHIELD1"/>
<connect gate="G$1" pin="G2" pad="SHIELD2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:44435040/1"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DB15G" urn="urn:adsk.eagle:component:44435043/1" prefix="J" library_version="35" library_locally_modified="yes">
<gates>
<gate name="G$1" symbol="F15G" x="0" y="0"/>
</gates>
<devices>
<device name="-VM" package="DS1034-15">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="10" pad="10"/>
<connect gate="G$1" pin="11" pad="11"/>
<connect gate="G$1" pin="12" pad="12"/>
<connect gate="G$1" pin="13" pad="13"/>
<connect gate="G$1" pin="14" pad="14"/>
<connect gate="G$1" pin="15" pad="15"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$1" pin="G1" pad="SHIELD1"/>
<connect gate="G$1" pin="G2" pad="SHIELD2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:44435038/1"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DB9G" urn="urn:adsk.eagle:component:44435045/1" prefix="J" library_version="35" library_locally_modified="yes">
<gates>
<gate name="G$1" symbol="F09G" x="0" y="0"/>
</gates>
<devices>
<device name="-VF" package="DB9G-F">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
<connect gate="G$1" pin="8" pad="8"/>
<connect gate="G$1" pin="9" pad="9"/>
<connect gate="G$1" pin="G1" pad="SHIELD1"/>
<connect gate="G$1" pin="G2" pad="SHIELD2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:44435041/1"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PIN-7" prefix="J" library_version="35" library_locally_modified="yes">
<gates>
<gate name="G$1" symbol="PIN-7" x="0" y="0"/>
</gates>
<devices>
<device name="-PH-7MP" package="PH-7MP">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
<connect gate="G$1" pin="7" pad="7"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:44435042/1"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MF3.0_1X4" urn="urn:adsk.eagle:component:31813629/2" locally_modified="yes" prefix="J" library_version="35" library_locally_modified="yes">
<gates>
<gate name="G$1" symbol="PIN-4" x="0" y="0"/>
</gates>
<devices>
<device name="MR" package="MF3.0_1X4MR">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:31813567/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="MV" package="MF3.0_1X4MV">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MF3.0_1X3" urn="urn:adsk.eagle:component:31813630/2" locally_modified="yes" prefix="J" library_version="35" library_locally_modified="yes">
<gates>
<gate name="G$1" symbol="PIN-3" x="0" y="0"/>
</gates>
<devices>
<device name="MR" package="MF3.0_1X3MR">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:31813569/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="MV" package="MF3.0_1X3MV">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="J2" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="KLS1-603C" device="SLOT" package3d_urn="urn:adsk.eagle:package:44429192/2"/>
<part name="STAGE" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="DB25G" device="-VF" package3d_urn="urn:adsk.eagle:package:44435040/1"/>
<part name="STABLE" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="DB15G" device="-VM" package3d_urn="urn:adsk.eagle:package:44435038/1"/>
<part name="J4" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="DB9G" device="-VF" package3d_urn="urn:adsk.eagle:package:44435041/1"/>
<part name="Z2" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="PIN-7" device="-PH-7MP" package3d_urn="urn:adsk.eagle:package:44435042/1"/>
<part name="X" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="MF3.0_1X4" device="MV" value="MF3.0_1X4MV"/>
<part name="Y" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="MF3.0_1X4" device="MV" value="MF3.0_1X4MV"/>
<part name="Z" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="MF3.0_1X4" device="MV" value="MF3.0_1X4MV"/>
<part name="HALLZ" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="MF3.0_1X3" device="MV" value="MF3.0_1X3MV"/>
<part name="HALLX" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="MF3.0_1X3" device="MV" value="MF3.0_1X3MV"/>
<part name="HALLY" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="MF3.0_1X3" device="MV" value="MF3.0_1X3MV"/>
<part name="HALL" library="snx_con" library_urn="urn:adsk.eagle:library:31813248" deviceset="MF3.0_1X3" device="MV" value="MF3.0_1X3MV"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="J2" gate="G$1" x="127" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="129.54" y="101.6" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="129.54" y="149.86" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="J2" gate="G$2" x="127" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="129.54" y="55.88" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="129.54" y="106.68" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="J2" gate="G$3" x="78.74" y="10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="81.28" y="-12.7" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="81.28" y="35.56" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="J2" gate="G$4" x="78.74" y="-35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="81.28" y="-58.42" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="81.28" y="-7.62" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="STAGE" gate="G$1" x="180.34" y="121.92" smashed="yes">
<attribute name="VALUE" x="176.53" y="100.965" size="1.778" layer="96"/>
<attribute name="NAME" x="176.53" y="140.97" size="1.778" layer="95"/>
</instance>
<instance part="STABLE" gate="G$1" x="142.24" y="-58.42" smashed="yes">
<attribute name="VALUE" x="137.795" y="-74.295" size="1.778" layer="96"/>
<attribute name="NAME" x="138.43" y="-21.59" size="1.778" layer="95"/>
</instance>
<instance part="J4" gate="G$1" x="180.34" y="86.36" smashed="yes">
<attribute name="VALUE" x="176.53" y="75.565" size="1.778" layer="96"/>
<attribute name="NAME" x="176.53" y="95.25" size="1.778" layer="95"/>
</instance>
<instance part="Z2" gate="G$1" x="180.34" y="-12.7" smashed="yes">
<attribute name="NAME" x="177.8" y="0" size="1.778" layer="95"/>
<attribute name="VALUE" x="177.8" y="-27.94" size="1.778" layer="96"/>
</instance>
<instance part="X" gate="G$1" x="144.78" y="25.4" smashed="yes">
<attribute name="NAME" x="142.24" y="35.56" size="1.778" layer="95"/>
<attribute name="VALUE" x="142.24" y="15.24" size="1.778" layer="96"/>
</instance>
<instance part="Y" gate="G$1" x="144.78" y="2.54" smashed="yes">
<attribute name="NAME" x="142.24" y="12.7" size="1.778" layer="95"/>
<attribute name="VALUE" x="142.24" y="-7.62" size="1.778" layer="96"/>
</instance>
<instance part="Z" gate="G$1" x="180.34" y="-60.96" smashed="yes">
<attribute name="NAME" x="177.8" y="-50.8" size="1.778" layer="95"/>
<attribute name="VALUE" x="177.8" y="-71.12" size="1.778" layer="96"/>
</instance>
<instance part="HALLZ" gate="G$1" x="180.34" y="-40.64" smashed="yes">
<attribute name="NAME" x="177.8" y="-33.02" size="1.778" layer="95"/>
<attribute name="VALUE" x="180.34" y="-48.26" size="1.778" layer="96"/>
</instance>
<instance part="HALLX" gate="G$1" x="144.78" y="-15.24" smashed="yes">
<attribute name="NAME" x="142.24" y="-7.62" size="1.778" layer="95"/>
<attribute name="VALUE" x="142.24" y="-25.4" size="1.778" layer="96"/>
</instance>
<instance part="HALLY" gate="G$1" x="144.78" y="-35.56" smashed="yes">
<attribute name="NAME" x="142.24" y="-27.94" size="1.778" layer="95"/>
<attribute name="VALUE" x="142.24" y="-45.72" size="1.778" layer="96"/>
</instance>
<instance part="HALL" gate="G$1" x="182.88" y="63.5" smashed="yes">
<attribute name="NAME" x="180.34" y="71.12" size="1.778" layer="95"/>
<attribute name="VALUE" x="180.34" y="53.34" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
<bus name="+5V,D[1..31],GND">
<segment>
<wire x1="142.24" y1="55.88" x2="142.24" y2="144.78" width="0.762" layer="92"/>
<wire x1="142.24" y1="144.78" x2="165.1" y2="144.78" width="0.762" layer="92"/>
<wire x1="165.1" y1="144.78" x2="165.1" y2="55.88" width="0.762" layer="92"/>
<label x="144.78" y="147.32" size="1.778" layer="95"/>
<wire x1="165.1" y1="144.78" x2="195.58" y2="144.78" width="0.762" layer="92"/>
<wire x1="195.58" y1="144.78" x2="195.58" y2="55.88" width="0.762" layer="92"/>
</segment>
</bus>
<bus name="+5V,D[32..60],GND">
<segment>
<wire x1="96.52" y1="-71.12" x2="96.52" y2="38.1" width="0.762" layer="92"/>
<wire x1="96.52" y1="38.1" x2="127" y2="38.1" width="0.762" layer="92"/>
<wire x1="127" y1="38.1" x2="165.1" y2="38.1" width="0.762" layer="92"/>
<wire x1="165.1" y1="38.1" x2="165.1" y2="-73.66" width="0.762" layer="92"/>
<label x="144.78" y="40.64" size="1.778" layer="95"/>
<wire x1="165.1" y1="38.1" x2="195.58" y2="38.1" width="0.762" layer="92"/>
<wire x1="195.58" y1="38.1" x2="195.58" y2="2.54" width="0.762" layer="92"/>
<wire x1="127" y1="38.1" x2="127" y2="-71.12" width="0.762" layer="92"/>
</segment>
</bus>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="J2" gate="G$3" pin="2"/>
<wire x1="86.36" y1="-5.08" x2="96.52" y2="-5.08" width="0.1524" layer="91"/>
<label x="88.9" y="-5.08" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STAGE" gate="G$1" pin="G1"/>
<wire x1="187.96" y1="139.7" x2="195.58" y2="139.7" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="STAGE" gate="G$1" pin="G2"/>
<wire x1="187.96" y1="104.14" x2="195.58" y2="104.14" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="G1"/>
<wire x1="187.96" y1="93.98" x2="195.58" y2="93.98" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="G2"/>
<wire x1="187.96" y1="78.74" x2="195.58" y2="78.74" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="G1"/>
<wire x1="149.86" y1="-48.26" x2="165.1" y2="-48.26" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="G2"/>
<wire x1="149.86" y1="-71.12" x2="165.1" y2="-71.12" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="HALL" gate="G$1" pin="2"/>
<wire x1="175.26" y1="63.5" x2="165.1" y2="63.5" width="0.1524" layer="91"/>
<label x="170.18" y="63.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="J2" gate="G$3" pin="1"/>
<wire x1="86.36" y1="-7.62" x2="96.52" y2="-7.62" width="0.1524" layer="91"/>
<label x="88.9" y="-7.62" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALL" gate="G$1" pin="1"/>
<wire x1="175.26" y1="66.04" x2="165.1" y2="66.04" width="0.1524" layer="91"/>
<label x="170.18" y="66.04" size="1.778" layer="95"/>
</segment>
</net>
<net name="D1" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="1"/>
<wire x1="172.72" y1="137.16" x2="165.1" y2="137.16" width="0.1524" layer="91"/>
<label x="167.64" y="137.16" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="1"/>
<wire x1="134.62" y1="106.68" x2="142.24" y2="106.68" width="0.1524" layer="91"/>
<label x="137.16" y="106.68" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="1"/>
<wire x1="172.72" y1="91.44" x2="165.1" y2="91.44" width="0.1524" layer="91"/>
<label x="167.64" y="91.44" size="1.778" layer="95"/>
</segment>
</net>
<net name="D2" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="2"/>
<wire x1="172.72" y1="134.62" x2="165.1" y2="134.62" width="0.1524" layer="91"/>
<label x="167.64" y="134.62" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="2"/>
<wire x1="134.62" y1="109.22" x2="142.24" y2="109.22" width="0.1524" layer="91"/>
<label x="137.16" y="109.22" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="2"/>
<wire x1="172.72" y1="88.9" x2="165.1" y2="88.9" width="0.1524" layer="91"/>
<label x="167.64" y="88.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="D3" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="3"/>
<wire x1="172.72" y1="132.08" x2="165.1" y2="132.08" width="0.1524" layer="91"/>
<label x="167.64" y="132.08" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="3"/>
<wire x1="134.62" y1="111.76" x2="142.24" y2="111.76" width="0.1524" layer="91"/>
<label x="137.16" y="111.76" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="3"/>
<wire x1="172.72" y1="86.36" x2="165.1" y2="86.36" width="0.1524" layer="91"/>
<label x="167.64" y="86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="D4" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="4"/>
<wire x1="172.72" y1="129.54" x2="165.1" y2="129.54" width="0.1524" layer="91"/>
<label x="167.64" y="129.54" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="4"/>
<wire x1="134.62" y1="114.3" x2="142.24" y2="114.3" width="0.1524" layer="91"/>
<label x="137.16" y="114.3" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="4"/>
<wire x1="172.72" y1="83.82" x2="165.1" y2="83.82" width="0.1524" layer="91"/>
<label x="167.64" y="83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="D6" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="6"/>
<wire x1="172.72" y1="124.46" x2="165.1" y2="124.46" width="0.1524" layer="91"/>
<label x="167.64" y="124.46" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="6"/>
<wire x1="134.62" y1="119.38" x2="142.24" y2="119.38" width="0.1524" layer="91"/>
<label x="137.16" y="119.38" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="6"/>
<wire x1="187.96" y1="88.9" x2="195.58" y2="88.9" width="0.1524" layer="91"/>
<label x="190.5" y="88.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="D5" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="5"/>
<wire x1="172.72" y1="127" x2="165.1" y2="127" width="0.1524" layer="91"/>
<label x="167.64" y="127" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="5"/>
<wire x1="134.62" y1="116.84" x2="142.24" y2="116.84" width="0.1524" layer="91"/>
<label x="137.16" y="116.84" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="5"/>
<wire x1="172.72" y1="81.28" x2="165.1" y2="81.28" width="0.1524" layer="91"/>
<label x="167.64" y="81.28" size="1.778" layer="95"/>
</segment>
</net>
<net name="D7" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="7"/>
<wire x1="172.72" y1="121.92" x2="165.1" y2="121.92" width="0.1524" layer="91"/>
<label x="167.64" y="121.92" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="7"/>
<wire x1="134.62" y1="121.92" x2="142.24" y2="121.92" width="0.1524" layer="91"/>
<label x="137.16" y="121.92" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="7"/>
<wire x1="187.96" y1="86.36" x2="195.58" y2="86.36" width="0.1524" layer="91"/>
<label x="190.5" y="86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="D8" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="8"/>
<wire x1="172.72" y1="119.38" x2="165.1" y2="119.38" width="0.1524" layer="91"/>
<label x="167.64" y="119.38" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="8"/>
<wire x1="134.62" y1="124.46" x2="142.24" y2="124.46" width="0.1524" layer="91"/>
<label x="137.16" y="124.46" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="8"/>
<wire x1="187.96" y1="83.82" x2="195.58" y2="83.82" width="0.1524" layer="91"/>
<label x="190.5" y="83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="D9" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="9"/>
<wire x1="172.72" y1="116.84" x2="165.1" y2="116.84" width="0.1524" layer="91"/>
<label x="167.64" y="116.84" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="9"/>
<wire x1="134.62" y1="127" x2="142.24" y2="127" width="0.1524" layer="91"/>
<label x="137.16" y="127" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J4" gate="G$1" pin="9"/>
<wire x1="187.96" y1="81.28" x2="195.58" y2="81.28" width="0.1524" layer="91"/>
<label x="190.5" y="81.28" size="1.778" layer="95"/>
</segment>
</net>
<net name="D10" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="10"/>
<wire x1="172.72" y1="114.3" x2="165.1" y2="114.3" width="0.1524" layer="91"/>
<label x="167.64" y="114.3" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="10"/>
<wire x1="134.62" y1="129.54" x2="142.24" y2="129.54" width="0.1524" layer="91"/>
<label x="137.16" y="129.54" size="1.778" layer="95"/>
</segment>
</net>
<net name="D11" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="11"/>
<wire x1="172.72" y1="111.76" x2="165.1" y2="111.76" width="0.1524" layer="91"/>
<label x="167.64" y="111.76" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="11"/>
<wire x1="134.62" y1="132.08" x2="142.24" y2="132.08" width="0.1524" layer="91"/>
<label x="137.16" y="132.08" size="1.778" layer="95"/>
</segment>
</net>
<net name="D12" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="12"/>
<wire x1="172.72" y1="109.22" x2="165.1" y2="109.22" width="0.1524" layer="91"/>
<label x="167.64" y="109.22" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="12"/>
<wire x1="134.62" y1="134.62" x2="142.24" y2="134.62" width="0.1524" layer="91"/>
<label x="137.16" y="134.62" size="1.778" layer="95"/>
</segment>
</net>
<net name="D13" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="13"/>
<wire x1="172.72" y1="106.68" x2="165.1" y2="106.68" width="0.1524" layer="91"/>
<label x="167.64" y="106.68" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="13"/>
<wire x1="134.62" y1="137.16" x2="142.24" y2="137.16" width="0.1524" layer="91"/>
<label x="137.16" y="137.16" size="1.778" layer="95"/>
</segment>
</net>
<net name="D14" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="14"/>
<wire x1="187.96" y1="137.16" x2="195.58" y2="137.16" width="0.1524" layer="91"/>
<label x="190.5" y="137.16" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="14"/>
<wire x1="134.62" y1="139.7" x2="142.24" y2="139.7" width="0.1524" layer="91"/>
<label x="137.16" y="139.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="D15" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="15"/>
<wire x1="187.96" y1="134.62" x2="195.58" y2="134.62" width="0.1524" layer="91"/>
<label x="190.5" y="134.62" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="15"/>
<wire x1="134.62" y1="142.24" x2="142.24" y2="142.24" width="0.1524" layer="91"/>
<label x="137.16" y="142.24" size="1.778" layer="95"/>
</segment>
</net>
<net name="D16" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="16"/>
<wire x1="187.96" y1="132.08" x2="195.58" y2="132.08" width="0.1524" layer="91"/>
<label x="190.5" y="132.08" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="1"/>
<wire x1="134.62" y1="60.96" x2="142.24" y2="60.96" width="0.1524" layer="91"/>
<label x="137.16" y="60.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="D17" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="17"/>
<wire x1="187.96" y1="129.54" x2="195.58" y2="129.54" width="0.1524" layer="91"/>
<label x="190.5" y="129.54" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="2"/>
<wire x1="134.62" y1="63.5" x2="142.24" y2="63.5" width="0.1524" layer="91"/>
<label x="137.16" y="63.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="D18" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="18"/>
<wire x1="187.96" y1="127" x2="195.58" y2="127" width="0.1524" layer="91"/>
<label x="190.5" y="127" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="3"/>
<wire x1="134.62" y1="66.04" x2="142.24" y2="66.04" width="0.1524" layer="91"/>
<label x="137.16" y="66.04" size="1.778" layer="95"/>
</segment>
</net>
<net name="D19" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="19"/>
<wire x1="187.96" y1="124.46" x2="195.58" y2="124.46" width="0.1524" layer="91"/>
<label x="190.5" y="124.46" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="4"/>
<wire x1="134.62" y1="68.58" x2="142.24" y2="68.58" width="0.1524" layer="91"/>
<label x="137.16" y="68.58" size="1.778" layer="95"/>
</segment>
</net>
<net name="D20" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="20"/>
<wire x1="187.96" y1="121.92" x2="195.58" y2="121.92" width="0.1524" layer="91"/>
<label x="190.5" y="121.92" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="5"/>
<wire x1="134.62" y1="71.12" x2="142.24" y2="71.12" width="0.1524" layer="91"/>
<label x="137.16" y="71.12" size="1.778" layer="95"/>
</segment>
</net>
<net name="D21" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="21"/>
<wire x1="187.96" y1="119.38" x2="195.58" y2="119.38" width="0.1524" layer="91"/>
<label x="190.5" y="119.38" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="6"/>
<wire x1="134.62" y1="73.66" x2="142.24" y2="73.66" width="0.1524" layer="91"/>
<label x="137.16" y="73.66" size="1.778" layer="95"/>
</segment>
</net>
<net name="D22" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="22"/>
<wire x1="187.96" y1="116.84" x2="195.58" y2="116.84" width="0.1524" layer="91"/>
<label x="190.5" y="116.84" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="7"/>
<wire x1="134.62" y1="76.2" x2="142.24" y2="76.2" width="0.1524" layer="91"/>
<label x="137.16" y="76.2" size="1.778" layer="95"/>
</segment>
</net>
<net name="D23" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="23"/>
<wire x1="187.96" y1="114.3" x2="195.58" y2="114.3" width="0.1524" layer="91"/>
<label x="190.5" y="114.3" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="8"/>
<wire x1="134.62" y1="78.74" x2="142.24" y2="78.74" width="0.1524" layer="91"/>
<label x="137.16" y="78.74" size="1.778" layer="95"/>
</segment>
</net>
<net name="D24" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="24"/>
<wire x1="187.96" y1="111.76" x2="195.58" y2="111.76" width="0.1524" layer="91"/>
<label x="190.5" y="111.76" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="9"/>
<wire x1="134.62" y1="81.28" x2="142.24" y2="81.28" width="0.1524" layer="91"/>
<label x="137.16" y="81.28" size="1.778" layer="95"/>
</segment>
</net>
<net name="D25" class="0">
<segment>
<pinref part="STAGE" gate="G$1" pin="25"/>
<wire x1="187.96" y1="109.22" x2="195.58" y2="109.22" width="0.1524" layer="91"/>
<label x="190.5" y="109.22" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$2" pin="10"/>
<wire x1="134.62" y1="83.82" x2="142.24" y2="83.82" width="0.1524" layer="91"/>
<label x="137.16" y="83.82" size="1.778" layer="95"/>
</segment>
</net>
<net name="D32" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="16"/>
<wire x1="86.36" y1="-15.24" x2="96.52" y2="-15.24" width="0.1524" layer="91"/>
<label x="88.9" y="-15.24" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z2" gate="G$1" pin="1"/>
<wire x1="172.72" y1="-5.08" x2="165.1" y2="-5.08" width="0.1524" layer="91"/>
<label x="167.64" y="-5.08" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z" gate="G$1" pin="1"/>
<wire x1="172.72" y1="-55.88" x2="165.1" y2="-55.88" width="0.1524" layer="91"/>
<label x="167.64" y="-55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="D33" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="15"/>
<wire x1="86.36" y1="-17.78" x2="96.52" y2="-17.78" width="0.1524" layer="91"/>
<label x="88.9" y="-17.78" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z2" gate="G$1" pin="2"/>
<wire x1="172.72" y1="-7.62" x2="165.1" y2="-7.62" width="0.1524" layer="91"/>
<label x="167.64" y="-7.62" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z" gate="G$1" pin="2"/>
<wire x1="172.72" y1="-58.42" x2="165.1" y2="-58.42" width="0.1524" layer="91"/>
<label x="167.64" y="-58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="D34" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="14"/>
<wire x1="86.36" y1="-20.32" x2="96.52" y2="-20.32" width="0.1524" layer="91"/>
<label x="88.9" y="-20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z2" gate="G$1" pin="3"/>
<wire x1="172.72" y1="-10.16" x2="165.1" y2="-10.16" width="0.1524" layer="91"/>
<label x="167.64" y="-10.16" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z" gate="G$1" pin="3"/>
<wire x1="172.72" y1="-60.96" x2="165.1" y2="-60.96" width="0.1524" layer="91"/>
<label x="167.64" y="-60.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="D35" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="13"/>
<wire x1="86.36" y1="-22.86" x2="96.52" y2="-22.86" width="0.1524" layer="91"/>
<label x="88.9" y="-22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z2" gate="G$1" pin="4"/>
<wire x1="172.72" y1="-12.7" x2="165.1" y2="-12.7" width="0.1524" layer="91"/>
<label x="167.64" y="-12.7" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z" gate="G$1" pin="4"/>
<wire x1="172.72" y1="-63.5" x2="165.1" y2="-63.5" width="0.1524" layer="91"/>
<label x="167.64" y="-63.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="D36" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="12"/>
<wire x1="86.36" y1="-25.4" x2="96.52" y2="-25.4" width="0.1524" layer="91"/>
<label x="88.9" y="-25.4" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z2" gate="G$1" pin="5"/>
<wire x1="172.72" y1="-15.24" x2="165.1" y2="-15.24" width="0.1524" layer="91"/>
<label x="167.64" y="-15.24" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALLZ" gate="G$1" pin="1"/>
<wire x1="172.72" y1="-38.1" x2="165.1" y2="-38.1" width="0.1524" layer="91"/>
<label x="167.64" y="-38.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="D37" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="11"/>
<wire x1="86.36" y1="-27.94" x2="96.52" y2="-27.94" width="0.1524" layer="91"/>
<label x="88.9" y="-27.94" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z2" gate="G$1" pin="6"/>
<wire x1="172.72" y1="-17.78" x2="165.1" y2="-17.78" width="0.1524" layer="91"/>
<label x="167.64" y="-17.78" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALLZ" gate="G$1" pin="3"/>
<wire x1="172.72" y1="-43.18" x2="165.1" y2="-43.18" width="0.1524" layer="91"/>
<label x="167.64" y="-43.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="D38" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="10"/>
<wire x1="86.36" y1="-30.48" x2="96.52" y2="-30.48" width="0.1524" layer="91"/>
<label x="88.9" y="-30.48" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="Z2" gate="G$1" pin="7"/>
<wire x1="172.72" y1="-20.32" x2="165.1" y2="-20.32" width="0.1524" layer="91"/>
<label x="167.64" y="-20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALLZ" gate="G$1" pin="2"/>
<wire x1="172.72" y1="-40.64" x2="165.1" y2="-40.64" width="0.1524" layer="91"/>
<label x="167.64" y="-40.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="D39" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="9"/>
<wire x1="86.36" y1="-33.02" x2="96.52" y2="-33.02" width="0.1524" layer="91"/>
<label x="88.9" y="-33.02" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALLX" gate="G$1" pin="1"/>
<wire x1="137.16" y1="-12.7" x2="127" y2="-12.7" width="0.1524" layer="91"/>
<label x="132.08" y="-12.7" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="3"/>
<wire x1="134.62" y1="-55.88" x2="127" y2="-55.88" width="0.1524" layer="91"/>
<label x="129.54" y="-55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="D40" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="8"/>
<wire x1="86.36" y1="-35.56" x2="96.52" y2="-35.56" width="0.1524" layer="91"/>
<label x="88.9" y="-35.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALLX" gate="G$1" pin="2"/>
<wire x1="137.16" y1="-15.24" x2="127" y2="-15.24" width="0.1524" layer="91"/>
<label x="132.08" y="-15.24" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="2"/>
<wire x1="134.62" y1="-53.34" x2="127" y2="-53.34" width="0.1524" layer="91"/>
<label x="129.54" y="-53.34" size="1.778" layer="95"/>
</segment>
</net>
<net name="D41" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="7"/>
<wire x1="86.36" y1="-38.1" x2="96.52" y2="-38.1" width="0.1524" layer="91"/>
<label x="88.9" y="-38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALLX" gate="G$1" pin="3"/>
<wire x1="137.16" y1="-17.78" x2="127" y2="-17.78" width="0.1524" layer="91"/>
<label x="132.08" y="-17.78" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="1"/>
<wire x1="134.62" y1="-50.8" x2="127" y2="-50.8" width="0.1524" layer="91"/>
<label x="129.54" y="-50.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="D42" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="6"/>
<wire x1="86.36" y1="-40.64" x2="96.52" y2="-40.64" width="0.1524" layer="91"/>
<label x="88.9" y="-40.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="D43" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="5"/>
<wire x1="86.36" y1="-43.18" x2="96.52" y2="-43.18" width="0.1524" layer="91"/>
<label x="88.9" y="-43.18" size="1.778" layer="95"/>
</segment>
</net>
<net name="D44" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="4"/>
<wire x1="86.36" y1="-45.72" x2="96.52" y2="-45.72" width="0.1524" layer="91"/>
<label x="88.9" y="-45.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="D45" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="3"/>
<wire x1="86.36" y1="-48.26" x2="96.52" y2="-48.26" width="0.1524" layer="91"/>
<label x="88.9" y="-48.26" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALLY" gate="G$1" pin="1"/>
<wire x1="137.16" y1="-33.02" x2="127" y2="-33.02" width="0.1524" layer="91"/>
<label x="132.08" y="-33.02" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="11"/>
<wire x1="149.86" y1="-55.88" x2="165.1" y2="-55.88" width="0.1524" layer="91"/>
<label x="154.94" y="-55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="D46" class="0">
<segment>
<pinref part="J2" gate="G$4" pin="2"/>
<wire x1="86.36" y1="-50.8" x2="96.52" y2="-50.8" width="0.1524" layer="91"/>
<label x="88.9" y="-50.8" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALLY" gate="G$1" pin="2"/>
<wire x1="137.16" y1="-35.56" x2="127" y2="-35.56" width="0.1524" layer="91"/>
<label x="132.08" y="-35.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="10"/>
<wire x1="149.86" y1="-53.34" x2="165.1" y2="-53.34" width="0.1524" layer="91"/>
<label x="154.94" y="-53.34" size="1.778" layer="95"/>
</segment>
</net>
<net name="D47" class="0">
<segment>
<pinref part="HALLY" gate="G$1" pin="3"/>
<wire x1="137.16" y1="-38.1" x2="127" y2="-38.1" width="0.1524" layer="91"/>
<label x="132.08" y="-38.1" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$4" pin="1"/>
<wire x1="86.36" y1="-53.34" x2="96.52" y2="-53.34" width="0.1524" layer="91"/>
<label x="88.9" y="-53.34" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="9"/>
<wire x1="149.86" y1="-50.8" x2="165.1" y2="-50.8" width="0.1524" layer="91"/>
<label x="154.94" y="-50.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="D48" class="0">
<segment>
<pinref part="X" gate="G$1" pin="1"/>
<wire x1="137.16" y1="30.48" x2="127" y2="30.48" width="0.1524" layer="91"/>
<label x="129.54" y="30.48" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="15"/>
<wire x1="86.36" y1="27.94" x2="96.52" y2="27.94" width="0.1524" layer="91"/>
<label x="88.9" y="27.94" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="12"/>
<wire x1="149.86" y1="-58.42" x2="165.1" y2="-58.42" width="0.1524" layer="91"/>
<label x="154.94" y="-58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="D49" class="0">
<segment>
<pinref part="X" gate="G$1" pin="2"/>
<wire x1="137.16" y1="27.94" x2="127" y2="27.94" width="0.1524" layer="91"/>
<label x="129.54" y="27.94" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="14"/>
<wire x1="86.36" y1="25.4" x2="96.52" y2="25.4" width="0.1524" layer="91"/>
<label x="88.9" y="25.4" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="5"/>
<wire x1="134.62" y1="-60.96" x2="127" y2="-60.96" width="0.1524" layer="91"/>
<label x="129.54" y="-60.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="D50" class="0">
<segment>
<pinref part="X" gate="G$1" pin="3"/>
<wire x1="137.16" y1="25.4" x2="127" y2="25.4" width="0.1524" layer="91"/>
<label x="129.54" y="25.4" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="13"/>
<wire x1="86.36" y1="22.86" x2="96.52" y2="22.86" width="0.1524" layer="91"/>
<label x="88.9" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="4"/>
<wire x1="134.62" y1="-58.42" x2="127" y2="-58.42" width="0.1524" layer="91"/>
<label x="129.54" y="-58.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="D51" class="0">
<segment>
<pinref part="X" gate="G$1" pin="4"/>
<wire x1="137.16" y1="22.86" x2="127" y2="22.86" width="0.1524" layer="91"/>
<label x="129.54" y="22.86" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="12"/>
<wire x1="86.36" y1="20.32" x2="96.52" y2="20.32" width="0.1524" layer="91"/>
<label x="88.9" y="20.32" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="13"/>
<wire x1="149.86" y1="-60.96" x2="165.1" y2="-60.96" width="0.1524" layer="91"/>
<label x="154.94" y="-60.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="D52" class="0">
<segment>
<pinref part="Y" gate="G$1" pin="1"/>
<wire x1="137.16" y1="7.62" x2="127" y2="7.62" width="0.1524" layer="91"/>
<label x="129.54" y="7.62" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="11"/>
<wire x1="86.36" y1="17.78" x2="96.52" y2="17.78" width="0.1524" layer="91"/>
<label x="88.9" y="17.78" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="14"/>
<wire x1="149.86" y1="-63.5" x2="165.1" y2="-63.5" width="0.1524" layer="91"/>
<label x="154.94" y="-63.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="D53" class="0">
<segment>
<pinref part="Y" gate="G$1" pin="2"/>
<wire x1="137.16" y1="5.08" x2="127" y2="5.08" width="0.1524" layer="91"/>
<label x="129.54" y="5.08" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="10"/>
<wire x1="86.36" y1="15.24" x2="96.52" y2="15.24" width="0.1524" layer="91"/>
<label x="88.9" y="15.24" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="7"/>
<wire x1="134.62" y1="-66.04" x2="127" y2="-66.04" width="0.1524" layer="91"/>
<label x="129.54" y="-66.04" size="1.778" layer="95"/>
</segment>
</net>
<net name="D54" class="0">
<segment>
<pinref part="Y" gate="G$1" pin="3"/>
<wire x1="137.16" y1="2.54" x2="127" y2="2.54" width="0.1524" layer="91"/>
<label x="129.54" y="2.54" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="9"/>
<wire x1="86.36" y1="12.7" x2="96.52" y2="12.7" width="0.1524" layer="91"/>
<label x="88.9" y="12.7" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="6"/>
<wire x1="134.62" y1="-63.5" x2="127" y2="-63.5" width="0.1524" layer="91"/>
<label x="129.54" y="-63.5" size="1.778" layer="95"/>
</segment>
</net>
<net name="D55" class="0">
<segment>
<pinref part="Y" gate="G$1" pin="4"/>
<wire x1="137.16" y1="0" x2="127" y2="0" width="0.1524" layer="91"/>
<label x="129.54" y="0" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="8"/>
<wire x1="86.36" y1="10.16" x2="96.52" y2="10.16" width="0.1524" layer="91"/>
<label x="88.9" y="10.16" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="STABLE" gate="G$1" pin="15"/>
<wire x1="149.86" y1="-66.04" x2="165.1" y2="-66.04" width="0.1524" layer="91"/>
<label x="154.94" y="-66.04" size="1.778" layer="95"/>
</segment>
</net>
<net name="D56" class="0">
<segment>
<pinref part="J2" gate="G$3" pin="7"/>
<wire x1="86.36" y1="7.62" x2="96.52" y2="7.62" width="0.1524" layer="91"/>
<label x="88.9" y="7.62" size="1.778" layer="95"/>
</segment>
</net>
<net name="D57" class="0">
<segment>
<pinref part="J2" gate="G$3" pin="6"/>
<wire x1="86.36" y1="5.08" x2="96.52" y2="5.08" width="0.1524" layer="91"/>
<label x="88.9" y="5.08" size="1.778" layer="95"/>
</segment>
</net>
<net name="D58" class="0">
<segment>
<pinref part="J2" gate="G$3" pin="5"/>
<wire x1="86.36" y1="2.54" x2="96.52" y2="2.54" width="0.1524" layer="91"/>
<label x="88.9" y="2.54" size="1.778" layer="95"/>
</segment>
</net>
<net name="D59" class="0">
<segment>
<pinref part="J2" gate="G$3" pin="4"/>
<wire x1="86.36" y1="0" x2="96.52" y2="0" width="0.1524" layer="91"/>
<label x="88.9" y="0" size="1.778" layer="95"/>
</segment>
</net>
<net name="D26" class="0">
<segment>
<pinref part="J2" gate="G$2" pin="11"/>
<wire x1="134.62" y1="86.36" x2="142.24" y2="86.36" width="0.1524" layer="91"/>
<label x="137.16" y="86.36" size="1.778" layer="95"/>
</segment>
</net>
<net name="D27" class="0">
<segment>
<pinref part="J2" gate="G$2" pin="12"/>
<wire x1="134.62" y1="88.9" x2="142.24" y2="88.9" width="0.1524" layer="91"/>
<label x="137.16" y="88.9" size="1.778" layer="95"/>
</segment>
</net>
<net name="D28" class="0">
<segment>
<pinref part="J2" gate="G$2" pin="13"/>
<wire x1="134.62" y1="91.44" x2="142.24" y2="91.44" width="0.1524" layer="91"/>
<label x="137.16" y="91.44" size="1.778" layer="95"/>
</segment>
</net>
<net name="D29" class="0">
<segment>
<pinref part="J2" gate="G$2" pin="14"/>
<wire x1="134.62" y1="93.98" x2="142.24" y2="93.98" width="0.1524" layer="91"/>
<label x="137.16" y="93.98" size="1.778" layer="95"/>
</segment>
</net>
<net name="D30" class="0">
<segment>
<pinref part="J2" gate="G$2" pin="15"/>
<wire x1="134.62" y1="96.52" x2="142.24" y2="96.52" width="0.1524" layer="91"/>
<label x="137.16" y="96.52" size="1.778" layer="95"/>
</segment>
</net>
<net name="D31" class="0">
<segment>
<pinref part="J2" gate="G$2" pin="16"/>
<wire x1="134.62" y1="99.06" x2="142.24" y2="99.06" width="0.1524" layer="91"/>
<label x="137.16" y="99.06" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="HALL" gate="G$1" pin="3"/>
<wire x1="175.26" y1="60.96" x2="165.1" y2="60.96" width="0.1524" layer="91"/>
<label x="170.18" y="60.96" size="1.778" layer="95"/>
</segment>
</net>
<net name="D60" class="0">
<segment>
<pinref part="STABLE" gate="G$1" pin="8"/>
<wire x1="134.62" y1="-68.58" x2="127" y2="-68.58" width="0.1524" layer="91"/>
<label x="129.54" y="-68.58" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="J2" gate="G$3" pin="3"/>
<wire x1="86.36" y1="-2.54" x2="96.52" y2="-2.54" width="0.1524" layer="91"/>
<label x="88.9" y="-2.54" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
