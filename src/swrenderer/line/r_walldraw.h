//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//

#pragma once

#include "swrenderer/viewport/r_walldrawer.h"
#include "r_line.h"

class FTexture;
struct FLightNode;
struct seg_t;
struct FLightNode;
struct FDynamicColormap;

namespace swrenderer
{
	class RenderThread;
	struct DrawSegment;
	struct FWallCoords;
	class ProjectedWallLine;
	class ProjectedWallTexcoords;
	struct WallSampler;

	class RenderWallPart
	{
	public:
		RenderWallPart(RenderThread *thread);

		void Render(
			const WallDrawerArgs &drawerargs,
			sector_t *frontsector,
			seg_t *curline,
			const FWallCoords &WallC,
			FTexture *rw_pic,
			int x1,
			int x2,
			const short *walltop,
			const short *wallbottom,
			double texturemid,
			float *swall,
			fixed_t *lwall,
			double yscale,
			double top,
			double bottom,
			bool mask,
			int wallshade,
			fixed_t xoffset,
			float light,
			float lightstep,
			FLightNode *light_list,
			bool foggy,
			FDynamicColormap *basecolormap);

		RenderThread *Thread = nullptr;

	private:
		void ProcessWallNP2(const short *uwal, const short *dwal, double texturemid, float *swal, fixed_t *lwal, double top, double bot);
		void ProcessWall(const short *uwal, const short *dwal, double texturemid, float *swal, fixed_t *lwal);
		void ProcessStripedWall(const short *uwal, const short *dwal, double texturemid, float *swal, fixed_t *lwal);
		void ProcessNormalWall(const short *uwal, const short *dwal, double texturemid, float *swal, fixed_t *lwal);
		void ProcessWallWorker(const short *uwal, const short *dwal, double texturemid, float *swal, fixed_t *lwal);
		void Draw1Column(int x, int y1, int y2, WallSampler &sampler);

		int x1 = 0;
		int x2 = 0;
		FTexture *rw_pic = nullptr;
		sector_t *frontsector = nullptr;
		seg_t *curline = nullptr;
		FWallCoords WallC;

		double yrepeat = 0.0;
		int wallshade = 0;
		fixed_t xoffset = 0;
		float light = 0.0f;
		float lightstep = 0.0f;
		bool foggy = false;
		FDynamicColormap *basecolormap = nullptr;
		FLightNode *light_list = nullptr;
		bool mask = false;

		WallDrawerArgs drawerargs;
	};

	struct WallSampler
	{
		WallSampler() { }
		WallSampler(int y1, double texturemid, float swal, double yrepeat, fixed_t xoffset, double xmagnitude, FTexture *texture);

		uint32_t uv_pos;
		uint32_t uv_step;
		uint32_t uv_max;

		const BYTE *source;
		const BYTE *source2;
		uint32_t texturefracx;
		uint32_t height;
	};
}
