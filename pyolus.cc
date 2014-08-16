#include <string>
#include <boost/python.hpp>
#include "addsynth.h"

namespace bp = boost::python;

std::string adds_get_filename(Addsynth const& self)
{
	return std::string(self._filename);
}

void adds_set_filename(Addsynth & self, std::string const& name)
{
	strncpy(self._filename, name.c_str(), sizeof(self._filename));
}

std::string adds_get_stopname(Addsynth const& self)
{
	return std::string(self._stopname);
}

BOOST_PYTHON_MODULE(pyolus)
{
	bp::class_<N_func>("N_func")
	.def("reset", &N_func::reset)
	.def("setv", &N_func::setv)
	.def("clrv", &N_func::clrv)
	.def("vs", &N_func::vs)
	.def("st", &N_func::st)
	.def("vi", &N_func::vi)
//	.def("write", &N_func::write)
//	.def("read", &N_func::read)
	;

	// resolve overloaded methods
	void (HN_func::*hn_setv_if)(int, float) = &HN_func::setv;
	void (HN_func::*hn_setv_iif)(int, int, float) = &HN_func::setv;
	void (HN_func::*hn_clrv_i)(int) = &HN_func::clrv;
	void (HN_func::*hn_clrv_ii)(int, int) = &HN_func::clrv;

	bp::class_<HN_func>("HN_func")
	.def("reset", &HN_func::reset)
	.def("setv", hn_setv_if)
	.def("clrv", hn_clrv_i)
	.def("setv", hn_setv_iif)
	.def("clrv", hn_clrv_ii)
	.def("vs", &HN_func::vs)
	.def("st", &HN_func::st)
	.def("vi", &HN_func::vi)
//	.def("write", &HN_func::write)
//	.def("read", &HN_func::read)
	;

	bp::class_<Addsynth>("Addsynth")
	.def("reset", &Addsynth::reset)
	.def("save", &Addsynth::save)
	.def("load", &Addsynth::load)
    
	.add_property("filename", &adds_get_filename, &adds_set_filename)
	.add_property("stopname", &adds_get_stopname)
//	.add_property("copyrite", )
//	.add_property("mnemonic", )
//	.add_property("comments", )
//	.add_property("reserved", )
	.def_readwrite("n0", &Addsynth::_n0)
	.def_readwrite("n1", &Addsynth::_n1)
	.def_readwrite("fn", &Addsynth::_fn)
	.def_readwrite("fd", &Addsynth::_fd)
//	N_func     _n_vol;
//	N_func     _n_off;
//	N_func     _n_ran;         
//	N_func     _n_ins;
//	N_func     _n_att;
//	N_func     _n_atd;         
//	N_func     _n_dct;
//	N_func     _n_dcd;         
//	HN_func    _h_lev;
//	HN_func    _h_ran;
//	HN_func    _h_att;
//	HN_func    _h_atp;

	.def_readwrite("pan", &Addsynth::_pan)
	.def_readwrite("del", &Addsynth::_del)
	;
}

