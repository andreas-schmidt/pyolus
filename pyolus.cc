#include <string>
#include <boost/python.hpp>
#include "addsynth.h"

namespace bp = boost::python;

// wrappers for char[] members
// TODO error handling in the setters
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

void adds_set_stopname(Addsynth & self, std::string const& name)
{
	strncpy(self._stopname, name.c_str(), sizeof(self._stopname));
}

std::string adds_get_copyrite(Addsynth const& self)
{
	return std::string(self._copyrite);
}

void adds_set_copyrite(Addsynth & self, std::string const& name)
{
	strncpy(self._copyrite, name.c_str(), sizeof(self._copyrite));
}

std::string adds_get_mnemonic(Addsynth const& self)
{
	return std::string(self._mnemonic);
}

void adds_set_mnemonic(Addsynth & self, std::string const& name)
{
	strncpy(self._mnemonic, name.c_str(), sizeof(self._mnemonic));
}

std::string adds_get_comments(Addsynth const& self)
{
	return std::string(self._comments);
}

void adds_set_comments(Addsynth & self, std::string const& name)
{
	strncpy(self._comments, name.c_str(), sizeof(self._comments));
}


BOOST_PYTHON_MODULE(pyolus)
{
	bp::scope().attr("N_NOTE") = N_NOTE;
	bp::scope().attr("N_HARM") = N_HARM;
	bp::scope().attr("NOTE_MIN") = NOTE_MIN;
	bp::scope().attr("NOTE_MAX") = NOTE_MAX;

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
	.add_property("stopname", &adds_get_stopname, &adds_set_stopname)
	.add_property("copyrite", &adds_get_copyrite, &adds_set_copyrite)
	.add_property("mnemonic", &adds_get_mnemonic, &adds_set_mnemonic)
	.add_property("comments", &adds_get_comments, &adds_set_comments)
//	.add_property("reserved", )
	.def_readwrite("n0", &Addsynth::_n0)
	.def_readwrite("n1", &Addsynth::_n1)
	.def_readwrite("fn", &Addsynth::_fn)
	.def_readwrite("fd", &Addsynth::_fd)
	.def_readonly("n_vol", &Addsynth::_n_vol)
	.def_readonly("n_off", &Addsynth::_n_off)
	.def_readonly("n_ran", &Addsynth::_n_ran)
	.def_readonly("n_ins", &Addsynth::_n_ins)
	.def_readonly("n_att", &Addsynth::_n_att)
	.def_readonly("n_atd", &Addsynth::_n_atd)
	.def_readonly("n_dct", &Addsynth::_n_dct)
	.def_readonly("n_dcd", &Addsynth::_n_dcd)
	.def_readonly("h_lev", &Addsynth::_h_lev)
	.def_readonly("h_ran", &Addsynth::_h_ran)
	.def_readonly("h_att", &Addsynth::_h_att)
	.def_readonly("h_atp", &Addsynth::_h_atp)

	.def_readwrite("pan", &Addsynth::_pan)
	.def_readwrite("del", &Addsynth::_del)
	;
}

