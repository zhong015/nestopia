////////////////////////////////////////////////////////////////////////////////////////
//
// Nestopia - NES/Famicom emulator written in C++
//
// Copyright (C) 2003-2007 Martin Freij
//
// This file is part of Nestopia.
//
// Nestopia is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// Nestopia is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Nestopia; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
////////////////////////////////////////////////////////////////////////////////////////

#ifndef NST_MAPPER_64_H
#define NST_MAPPER_64_H

#ifdef NST_PRAGMA_ONCE
#pragma once
#endif

namespace Nes
{
	namespace Core
	{
		class Mapper64 : public Mapper
		{
		public:

			explicit Mapper64(Context&);

		private:

			~Mapper64() {}

			void SubReset(bool);
			void SubSave(State::Saver&) const;
			void SubLoad(State::Loader&);
			void UpdatePrg();
			void UpdateChr() const;
			void Sync(Event,Input::Controllers*);

			NES_DECL_POKE( 8000 );
			NES_DECL_POKE( 8001 );
			NES_DECL_POKE( C000 );
			NES_DECL_POKE( C001 );
			NES_DECL_POKE( E000 );
			NES_DECL_POKE( E001 );

			struct Regs
			{
				void Reset();

				uint ctrl;
				byte chr[8];
				byte prg[3];
				byte padding;
			};

			struct Irq
			{
				Irq(Cpu&,Ppu&);

				void Update();

				enum
				{
					M2_CLOCK   = 4,
					A12_FILTER = 16,
					IRQ_DELAY  = 2,
					SOURCE_PPU = 0x0,
					SOURCE_CPU = 0x1,
					SOURCE     = 0x1
				};

				struct Unit
				{
					void Reset(bool);
					bool Clock();

					uint count;
					uint latch;
					ibool reload;
					ibool enabled;
				};

				typedef ClockUnits::A12<Unit&,A12_FILTER,IRQ_DELAY> A12;
				typedef ClockUnits::M2<Unit&,M2_CLOCK> M2;

				Unit unit;
				A12 a12;
				M2 m2;
			};

			Regs regs;
			Irq irq;
		};
	}
}

#endif
