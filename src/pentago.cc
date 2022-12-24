#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>

#include "neural/cmaes.h"
#include "pentago/position.h"
#include "selfplay/game.h"

namespace py = pybind11;

PYBIND11_MODULE(alpha_pentago, m) {
  m.doc() = "Alpha Pentago Python Library";

  // used for cmaes
  m.attr("NUM_WEIGHTS") = pentago::kNumWeights;
  m.def("fitnesses", &pentago::fitnesses);

  py::class_<pentago::Move>(m, "Move")
      .def(py::init<const std::string&>())
      .def("__str__", &pentago::Move::as_string)
      .def(py::self == py::self)
      .def(py::self != py::self);

  py::enum_<pentago::GameResult>(m, "GameResult")
      .value("WHITE_WON", pentago::GameResult::WHITE_WON)
      .value("BLACK_WON", pentago::GameResult::BLACK_WON)
      .value("DRAW", pentago::GameResult::DRAW)
      .value("UNDECIDED", pentago::GameResult::UNDECIDED)
      .export_values();

  py::class_<pentago::Game>(m, "Game")
      .def(py::init<>())
      .def("set_max_search_depth", &pentago::Game::SetMaxSearchDepth)
      .def("legal_moves", &pentago::Game::LegalMoves)
      .def("push", &pentago::Game::MakeMove)
      .def("pop", &pentago::Game::UnmakeMove)
      .def("compute_result", &pentago::Game::ComputeResult)
      .def("best_move", &pentago::Game::BestMove)
      .def("__str__", &pentago::Game::DebugString);
}