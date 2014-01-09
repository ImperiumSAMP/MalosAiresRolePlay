#if defined _impmap_included
	#endinput
#endif
#define _impmap_included

#define MAX_BUILDINGS_TO_REMOVE 500

enum BuildingToRemove {
    b_modelid,
	Float:b_fX,
	Float:b_fY,
	Float:b_fZ,
	Float:b_fRadius
};

new buildingsToRemove[MAX_BUILDINGS_TO_REMOVE][BuildingToRemove];
new buildingsToRemoveCount=0;
new __lastObject;

stock AddBuildingToRemove(build[BuildingToRemove]){
	if(buildingsToRemoveCount<MAX_BUILDINGS_TO_REMOVE){
		buildingsToRemove[buildingsToRemoveCount][b_modelid]=build[b_modelid];
		buildingsToRemove[buildingsToRemoveCount][b_fX]=build[b_fX];
		buildingsToRemove[buildingsToRemoveCount][b_fY]=build[b_fY];
		buildingsToRemove[buildingsToRemoveCount][b_fZ]=build[b_fZ];
		buildingsToRemove[buildingsToRemoveCount][b_fRadius]=build[b_fRadius];
		buildingsToRemoveCount++;
 	}
}

stock RemoveBuildingsForPlayer(playerid){
	for(new i=0; i< buildingsToRemoveCount;i++){
		RemoveBuildingForPlayerImp(playerid,buildingsToRemove[i]);
	}
}

stock RemoveBuildingForPlayerImp(playerid,building[BuildingToRemove]){
	RemoveBuildingForPlayer(playerid,building[b_modelid],building[b_fX],building[b_fY],building[b_fZ],building[b_fRadius]);
}

stock imp_strtok(string[],&idx,seperator = ' ')
{
	new ret[128], i = 0, len = strlen(string);
	while(string[idx] == seperator && idx < len) idx++;
	while(string[idx] != seperator && idx < len)
	{
	    ret[i] = string[idx];
	    i++;
		idx++;
	}
	while(string[idx] == seperator && idx < len) idx++;
	return ret;
}

stock LoadMapFiles(index[]){

	new mapname[256],
	File:hIndex, i;

	hIndex = fopen(index, io_read);
	while(fread(hIndex,mapname))
	{
		i=0;
		LoadMapFromFile(strtok(mapname,i,';'));
	}

	fclose(hIndex);

}

stock LoadMapFromFile(mapname[]){
	new File:hMap,
		currentObject[256];

	if(strlen(mapname) && mapname[0]!='/'){
		printf("[IMP-Map] Loading map %s;",mapname);

		hMap=fopen(mapname, io_read);
		while(fread(hMap,currentObject)){
			ParseMapLine(currentObject);
		}
		fclose(hMap);
	}
}

stock ParseMapLine(line[]){
	new funcName[256],idx;

	#if defined DEBUG
	printf("[IMP-Map] Parsing MapLine %s",line);
	#endif

	if(strlen(line) && line[0]!='/'){
		funcName=imp_strtok(line,idx,'(');

		if(strcmp(funcName,"CreateDynamicObject")==0)
		    __lastObject=ParseDynamicObject(line,idx);
		else if(strcmp(funcName,"CreateObject")==0)
            __lastObject=ParseObject(line,idx);
		else if(strcmp(funcName,"SetDynamicObjectMaterialText")==0)
			ParseDynamicObjectMaterialText(line,idx,__lastObject);
		else if(strcmp(funcName,"SetObjectMaterialText")==0)
			ParseObjectMaterialText(line,idx,__lastObject);
		else if(strcmp(funcName,"SetDynamicObjectMaterial")==0)
			ParseDynamicObjectMaterial(line,idx,__lastObject);
		else if(strcmp(funcName,"SetObjectMaterial")==0)
			ParseObjectMaterial(line,idx,__lastObject);
		else if(strcmp(funcName,"RemoveBuildingForPlayer")==0)
		    ParseRemoveBuildingForPlayer(line,idx);

	}
}

stock ParseDynamicObject(line[],idx){
        new objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz;

		objectid=strval(imp_strtok(line,idx,','));
		x=floatstr(imp_strtok(line,idx,','));
		y=floatstr(imp_strtok(line,idx,','));
		z=floatstr(imp_strtok(line,idx,','));
		rx=floatstr(imp_strtok(line,idx,','));
		ry=floatstr(imp_strtok(line,idx,','));
		rz=floatstr(imp_strtok(line,idx,')'));

		return CreateDynamicObject(objectid,x,y,z,rx,ry,rz);
}

stock ParseObject(line[],idx){
        new objectid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz;

		objectid=strval(imp_strtok(line,idx,','));
		x=floatstr(imp_strtok(line,idx,','));
		y=floatstr(imp_strtok(line,idx,','));
		z=floatstr(imp_strtok(line,idx,','));
		rx=floatstr(imp_strtok(line,idx,','));
		ry=floatstr(imp_strtok(line,idx,','));
		rz=floatstr(imp_strtok(line,idx,')'));

		return CreateObject(objectid,x,y,z,rx,ry,rz);
}

stock ParseDynamicObjectMaterial(line[],idx,oid){
        new matidx,modelid,txdname[256],texturename[256],materialcolor;

		matidx=strval(imp_strtok(line,idx,','));
		modelid=strval(imp_strtok(line,idx,','));
		txdname=imp_strtok(line,idx,',');
		texturename=imp_strtok(line,idx,',');
		materialcolor=strval(imp_strtok(line,idx,')'));
       	printf("[IMP-Map] Setting DynamicObjectMaterial to object %d Line: %s ",oid,line);
		SetDynamicObjectMaterial(oid,matidx,modelid,txdname,texturename,materialcolor);
}

stock ParseObjectMaterial(line[],idx,oid){
        new matidx,modelid,txdname[256],texturename[256],materialcolor;

		matidx=strval(imp_strtok(line,idx,','));
		modelid=strval(imp_strtok(line,idx,','));
		txdname=imp_strtok(line,idx,',');
		texturename=imp_strtok(line,idx,',');
		materialcolor=strval(imp_strtok(line,idx,')'));
       	printf("[IMP-Map] Setting ObjectMaterial to object %d Line: %s",oid,line);
		SetObjectMaterial(oid,matidx,modelid,txdname,texturename,materialcolor);
}

stock ParseDynamicObjectMaterialText(line[],idx,oid){
        new matidx,text[256],fontface[256],size,fontsize,bold,fontcolor,backcolor,textalignment;

		matidx=strval(imp_strtok(line,idx,','));
		text=imp_strtok(line,idx,',');
		size=strval(imp_strtok(line,idx,','));
		fontface=imp_strtok(line,idx,',');
		fontsize=strval(imp_strtok(line,idx,','));
		bold=strval(imp_strtok(line,idx,','));
		fontcolor=strval(imp_strtok(line,idx,','));
		backcolor=strval(imp_strtok(line,idx,','));
		textalignment=strval(imp_strtok(line,idx,')'));

		SetDynamicObjectMaterialText(oid,matidx,text,size,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
}

stock ParseObjectMaterialText(line[],idx,oid){
        new matidx,text[256],fontface[256],size,fontsize,bold,fontcolor,backcolor,textalignment;

		matidx=strval(imp_strtok(line,idx,','));
		text=imp_strtok(line,idx,',');
		size=strval(imp_strtok(line,idx,','));
		fontface=imp_strtok(line,idx,',');
		fontsize=strval(imp_strtok(line,idx,','));
		bold=strval(imp_strtok(line,idx,','));
		fontcolor=strval(imp_strtok(line,idx,','));
		backcolor=strval(imp_strtok(line,idx,','));
		textalignment=strval(imp_strtok(line,idx,')'));
		
		SetObjectMaterialText(oid,text,matidx,size,fontface,fontsize,bold,fontcolor,backcolor,textalignment);
}

stock ParseRemoveBuildingForPlayer(line[],idx){
        new b[BuildingToRemove];

        //descarto el playerid
		imp_strtok(line,idx,',');

		b[b_modelid]=strval(imp_strtok(line,idx,','));
		b[b_fX]=floatstr(imp_strtok(line,idx,','));
		b[b_fY]=floatstr(imp_strtok(line,idx,','));
		b[b_fZ]=floatstr(imp_strtok(line,idx,','));
		b[b_fRadius]=floatstr(imp_strtok(line,idx,')'));
		
		AddBuildingToRemove(b);
}
