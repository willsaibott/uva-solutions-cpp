/**
 * Guilherme de Novais Bordignon - UVA Judge Online Solution
 * uhunt page: https://uhunt.onlinejudge.org/id/899065
 *
 */

#include <bits/stdc++.h>

using namespace std;
typedef unsigned char byte;
typedef unsigned long long ull;
typedef long long ll;

namespace std {
  template<typename T, typename... Args>
  unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }
}

template <class T = size_t>
T getInput() {
  static T input;
  return (std::cin >> input, std::cin.ignore(), input);
}

inline const std::string& getln() {
  static std::string line;
  return (std::getline(std::cin, line), line);
}

struct Statement {
  std::string subject;
  std::string toBe;
  std::string statement;
  std::string author;
  bool isDeny;

  static std::string Impossible() {
    return "This is impossible.";
  }

  static  std::string notDeducible() {
    return "No facts are deducible.";
  }

  std::string as_answer() const {
    return subject + " " + toBe + " " + statement + ".";
  }

  Statement& read(std::istream& iss) {
    iss >> author >> subject >> toBe >> statement;
    author.pop_back(); // remove ":"
    isDeny = statement == "not";
    if (isDeny) {
      iss >> statement;
    }
    statement.pop_back(); // remove "."

    if (subject == "I") {
      subject = author;
    }
    return *this;
  }
};

enum class Inhabitant {
  Unknown,
  Devine,
  Evil,
  Human,
};

enum class Period {
  Unknown,
  Day,
  Night
};

enum class PossibleCombinations {
  Divine,
  Evil,
  HumanDay,
  HumanNight,
};

std::string to_string(Inhabitant hab) {
  switch (hab) {
    case Inhabitant::Devine: return "divine";
    case Inhabitant::Evil: return "evil";
    case Inhabitant::Human: return "human";
    default: break;
  }
  return "Unknown";
}

std::string to_string(Period period) {
  switch (period) {
  case Period::Day: return "day";
  case Period::Night: return "night";
  default: break;
  }
  return "Unknown";
}

class AbsurdException : public std::runtime_error {
  public:

    AbsurdException(): std::runtime_error(Statement::Impossible()) { }
};

class Solution {
public:

  std::map<std::string, std::set<PossibleCombinations>> subjectPossibleRaces;
  std::map<std::string, std::map<std::string, Inhabitant>> subjectSupposedRaces;
  std::map<std::string, std::map<std::string, std::set<Inhabitant>>> subjectSupposedNotRaces;
  std::map<std::string, std::map<std::string, bool>> subjectSupposedLiers;
  std::map<std::string, std::map<std::string, bool>> subjectSupposedTrusted;
  std::map<std::string, Period> subjectSupposedDayOrNight;
  std::map<std::string, Inhabitant> subjects;
  std::map<std::string, bool> lier;
  std::map<std::string, bool> truthTeller;
  std::set<std::string> inhabitants;
  Period period = Period::Unknown;

  void addInhabitant(std::string inhabitant) {
    inhabitants.insert(inhabitant);
    subjectPossibleRaces[inhabitant].insert(PossibleCombinations::Divine);
    subjectPossibleRaces[inhabitant].insert(PossibleCombinations::Evil);
    subjectPossibleRaces[inhabitant].insert(PossibleCombinations::HumanDay);
    subjectPossibleRaces[inhabitant].insert(PossibleCombinations::HumanNight);
    lier[inhabitant] = false;
    truthTeller[inhabitant] = false;
    subjects[inhabitant] = Inhabitant::Unknown;
  }

  Inhabitant getInhabitant(const std::string& str) {
    if (str == "human") return Inhabitant::Human;
    if (str == "evil") return Inhabitant::Evil;
    return Inhabitant::Devine;
  }

  Period getPeriod(const std::string& str) {
    if (str == "day") return Period::Day;
    return Period::Night;
  }

  void setAsHuman(const std::string& subject) {
    if (subjects[subject] != Inhabitant::Unknown && subjects[subject] != Inhabitant::Human)
      throw AbsurdException();
    subjects[subject] = Inhabitant::Human;

    if (subjectSupposedDayOrNight[subject] == Period::Night) {
      throw AbsurdException();
    }
    if (period == Period::Day) {
      setAsTrustedInternal(subject);
      subjectPossibleRaces[subject].erase(PossibleCombinations::HumanNight);
    }
    else if (period == Period::Night){
      setAsLierInternal(subject);
      subjectPossibleRaces[subject].erase(PossibleCombinations::HumanDay);
    }

    subjectPossibleRaces[subject].erase(PossibleCombinations::Divine);
    subjectPossibleRaces[subject].erase(PossibleCombinations::Evil);
  }

  void setAsDevine(const std::string& subject) {
    if (subjects[subject] != Inhabitant::Unknown && subjects[subject] != Inhabitant::Devine)
      throw AbsurdException();
    subjects[subject] = Inhabitant::Devine;
    setAsTrustedInternal(subject);
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanDay);
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanNight);
    subjectPossibleRaces[subject].erase(PossibleCombinations::Evil);
  }

  void setAsEvil(const std::string& subject) {
    if (subjects[subject] != Inhabitant::Unknown && subjects[subject] != Inhabitant::Evil)
      throw AbsurdException();
    subjects[subject] = Inhabitant::Evil;
    setAsLierInternal(subject);
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanDay);
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanNight);
    subjectPossibleRaces[subject].erase(PossibleCombinations::Divine);
  }

  void setPeriod(Period newPeriod) {
    if (period != Period::Unknown && period != newPeriod)
      throw AbsurdException();
    if (period == newPeriod) return;

    period = newPeriod;
    if (Period::Night == newPeriod) {
      for (const auto& hab : inhabitants) {
        setNotHumanDay(hab);
      }
    }
    else if (Period::Day == newPeriod) {
      for (const auto& hab : inhabitants) {
        setNotHumanNight(hab);
      }
    }
  }

  void setAsLierInternal(const std::string& subject) {
    if (truthTeller[subject]) {
      throw AbsurdException();
    }

    lier[subject] = true;
  }

  void setAsTrustedInternal(const std::string& subject) {
    if (lier[subject]) {
      throw AbsurdException();
    }

    truthTeller[subject] = true;
  }

  void setAsLier(const std::string& subject) {
    setAsLierInternal(subject);
    subjectPossibleRaces[subject].erase(PossibleCombinations::Divine);
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanDay);
    checkPossibleRaces(subject);
  }

  void setAsTrusted(const std::string& subject) {
    setAsTrustedInternal(subject);
    subjectPossibleRaces[subject].erase(PossibleCombinations::Evil);
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanNight);
    checkPossibleRaces(subject);
  }

  bool heSaysHeIsHuman(const std::string& subject) {
    return subjectSupposedRaces[subject][subject] == Inhabitant::Human;
  }

  bool heSaysOtherIsLying(const std::string& one, const std::string& another) {
    return subjectSupposedLiers[one][another];
  }

  void checkPossibleRaces(const std::string& subject) {
    if (subjectPossibleRaces[subject].size() == 1ull) {
      PossibleCombinations possible = *subjectPossibleRaces[subject].begin();
      if (possible == PossibleCombinations::HumanDay) {
        setPeriod(Period::Day);
        setAsHuman(subject);
      }
      else if (possible == PossibleCombinations::Divine) {
        setAsDevine(subject);
      }
      else if (possible == PossibleCombinations::HumanNight) {
        setPeriod(Period::Night);
        setAsHuman(subject);
      }
      else if (possible == PossibleCombinations::Evil) {
        setAsEvil(subject);
      }
      else {
        throw AbsurdException();
      }
    }
    else if (subjectPossibleRaces[subject].size() == 2ull) {
      PossibleCombinations possible1 = *subjectPossibleRaces[subject].begin();
      PossibleCombinations possible2 = *std::next(subjectPossibleRaces[subject].begin());
      if ((possible1 == PossibleCombinations::HumanNight && possible2 == PossibleCombinations::HumanDay) ||
          (possible1 == PossibleCombinations::HumanDay && possible2 == PossibleCombinations::HumanNight)) {
          setAsHuman(subject);
      }
      if ((possible1 == PossibleCombinations::HumanDay && possible2 == PossibleCombinations::Divine && period == Period::Day) ||
          (possible1 == PossibleCombinations::Divine && possible2 == PossibleCombinations::HumanDay && period == Period::Day)) {
          setAsTrustedInternal(subject);
      }
      if ((possible1 == PossibleCombinations::HumanNight && possible2 == PossibleCombinations::Evil && period == Period::Day) ||
          (possible1 == PossibleCombinations::Evil && possible2 == PossibleCombinations::HumanNight && period == Period::Night)) {
          setAsLierInternal(subject);
      }
    }
    else if (subjectPossibleRaces[subject].empty()) {
      throw AbsurdException();
    }
  }

  void setNotEvil(const std::string& subject) {
    subjectPossibleRaces[subject].erase(PossibleCombinations::Evil);
    checkPossibleRaces(subject);
  }

  void setNotHuman(const std::string& subject) {
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanDay);
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanNight);
    checkPossibleRaces(subject);
  }

  void setNotHumanDay(const std::string& subject) {
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanDay);
    checkPossibleRaces(subject);
  }

  void setNotHumanNight(const std::string& subject) {
    subjectPossibleRaces[subject].erase(PossibleCombinations::HumanNight);
    checkPossibleRaces(subject);
  }

  void setNotDivine(const std::string& subject) {
    subjectPossibleRaces[subject].erase(PossibleCombinations::Divine);
    checkPossibleRaces(subject);
  }

  bool process_negative(const Statement& statement) {
    if (statement.statement == "lying") {
      return process_not_lying_statement(statement);
    }

    if (statement.subject == "It") {
      return process_not_period_statement(statement);
    }

    return process_not_subject_statement(statement);
  }

  void checkIfNoInvalidTrustIssues(const Statement& statement) {
    if (subjectSupposedLiers[statement.subject][statement.author] &&
        subjectSupposedTrusted[statement.author][statement.subject])
    {
      throw AbsurdException();
    }
    if (subjectSupposedLiers[statement.author][statement.subject] &&
        subjectSupposedTrusted[statement.subject][statement.author])
    {
      throw AbsurdException();
    }
  }

  bool process_not_lying_statement(const Statement& statement) {
    if (statement.author != statement.subject) {
      considerOtherAsTrusted(statement);
    }

    // Ha! your friend is lying too!
    if (lier[statement.author]) {
      setAsLier(statement.subject);
    }
    // Aha! caught lying!
    else if (lier[statement.subject]) {
      setAsLier(statement.author);
    }
    else if (truthTeller[statement.author]) {
      setAsTrusted(statement.subject);
    }
    else if (truthTeller[statement.subject]) {
      setAsTrusted(statement.author);
    }

    checkIfNoInvalidTrustIssues(statement);
    return false;
  }

  bool process_lying_statement(const Statement& statement) {
    considerOtherAsLier(statement);

    // I am lying is an absurd! Are you ok?
    if (statement.author == statement.subject) {
      throw AbsurdException();
    }

    // Ha! you were caught lying about your friend!
    if (truthTeller[statement.subject]) {
      setAsLier(statement.author);
    }
    // We trust on the author, so the subject is a lier!
    else if (truthTeller[statement.author]) {
      setAsLier(statement.subject);
    }
    // author is lier, so subject is trustable
    else if (lier[statement.author]) {
      setAsTrusted(statement.subject);
    }
    else if (lier[statement.subject]) {
      setAsTrusted(statement.author);
    }

    if (heSaysHeIsHuman(statement.author)  &&
        heSaysHeIsHuman(statement.subject))
    {
      // There is, in fact one human that is telling the truth, so must be a Day
      setPeriod(Period::Day);
    }

    if (subjectSupposedDayOrNight[statement.author] == Period::Day &&
        heSaysHeIsHuman(statement.subject))
    {
      // subject is a lier, becuase if the author was lying, then it would be night
      // and humans lies at night
      setPeriod(Period::Day);
      setAsTrusted(statement.author);
      setAsEvil(statement.subject);
    }

    return false;
  }

  bool process_not_period_statement(const Statement& statement) {
    Period previous = subjectSupposedDayOrNight[statement.author];
    Period now = getPeriod(statement.statement);

    if (period == now) {
      setAsLier(statement.author);
    }
    else if (period != Period::Unknown) {
      setAsTrusted(statement.author);
    }

    if (lier[statement.author]) {
      setPeriod(now);
    }
    else if (truthTeller[statement.author]) {
      setPeriod(now == Period::Day ? Period::Night : Period::Day);
    }

    if (previous != Period::Unknown) {
      // Ha! contradiction, you said earlier the opposite, no you say it's not that period, hum?
      if (previous == now) {
        setAsLier(statement.author);
      }
    }
    else {
      subjectSupposedDayOrNight[statement.author] = now == Period::Day ? Period::Night : Period::Day;

      if (now == Period::Day) {
        // Evil Lier!
        if (subjectSupposedRaces[statement.author][statement.author] == Inhabitant::Human &&
            !subjectPossibleRaces[statement.author].count(PossibleCombinations::HumanNight)
          ) {
          setAsEvil(statement.author);
        }
      }

      return true;
    }
    return false;
  }

  bool process_period_statement(const Statement& statement) {
    Period itWas = subjectSupposedDayOrNight[statement.author];
    Period itIs = getPeriod(statement.statement);

    if (period == itIs) {
      setAsTrusted(statement.author);
    }
    else if (period != Period::Unknown) {
      setAsLier(statement.author);
    }

    if (truthTeller[statement.author]) {
      setPeriod(itIs);
    }
    else if (lier[statement.author]) {
      setPeriod(itIs == Period::Day ? Period::Night : Period::Day);
    }

    if (itIs == Period::Night) {
      // Evil Lier!
      if (heSaysHeIsHuman(statement.author)) {
        setAsEvil(statement.author);
      }
    }

    if (itWas != Period::Unknown) {
      // Ha! contradiction
      if (itWas != itIs) {
        setAsLier(statement.author);
        return true;
      }
    }
    else {
      subjectSupposedDayOrNight[statement.author] = itIs;
      return true;
    }

    return false;
  }

  void process_other_is_not_from_races(const Statement& statement) {
    if (subjectSupposedNotRaces[statement.author][statement.subject].size() == 3) {
      throw AbsurdException{};
    }
    else {
      setAsTrusted(statement.author);
      auto& heIsNotThisRaces = subjectSupposedNotRaces[statement.author][statement.subject];
      if (heIsNotThisRaces.count(Inhabitant::Human) && heIsNotThisRaces.count(Inhabitant::Evil)) {
        setAsDevine(statement.subject);
      }
      else if (heIsNotThisRaces.count(Inhabitant::Human) && heIsNotThisRaces.count(Inhabitant::Devine)) {
        if (statement.author == statement.subject) {
          throw AbsurdException{};
        }
        setAsEvil(statement.subject);
      }
      else if (heIsNotThisRaces.count(Inhabitant::Evil) && heIsNotThisRaces.count(Inhabitant::Devine)) {
        setAsHuman(statement.subject);
        if (statement.author == statement.subject) {
          setPeriod(Period::Day);
        }
      }
    }
  }

  void process_self_not_from_race(const Statement& statement) {
    Inhabitant IamNot = getInhabitant(statement.statement);

    // Impossible, evil beings only tell lies
    if (IamNot == Inhabitant::Devine) {
      setPeriod(Period::Day);
      setAsHuman(statement.author);
    }
    else if (IamNot == Inhabitant::Human) {
      setNotEvil(statement.author);
      setNotHumanDay(statement.author);
    }
    else if (IamNot == Inhabitant::Evil) {
      setNotHumanNight(statement.author);
    }
  }

  void process_lier_and_trust_for_negative(const Statement& statement) {
    Inhabitant heIsNot = getInhabitant(statement.statement);

    if (truthTeller[statement.author]) {
      if (Inhabitant::Devine == heIsNot) {
        setNotDivine(statement.subject);
      }
      else if (Inhabitant::Human == heIsNot) {
        setNotHuman(statement.subject);
      }
      else if (Inhabitant::Evil == heIsNot) {
        setNotEvil(statement.subject);
      }
    }
    else if (lier[statement.author]) {
      if (Inhabitant::Devine == heIsNot) {
        setAsDevine(statement.subject);
      }
      else if (Inhabitant::Human == heIsNot) {
        setAsHuman(statement.subject);
      }
      else if (Inhabitant::Evil == heIsNot) {
        setAsEvil(statement.subject);
      }
    }
  }

  bool process_not_subject_statement(const Statement& statement) {
    Inhabitant previous = subjectSupposedRaces[statement.author][statement.subject];
    Inhabitant now = getInhabitant(statement.statement);
    subjectSupposedNotRaces[statement.author][statement.subject].insert(now);

    if (previous != Inhabitant::Unknown) {
      // Ha! you are contradicting yourself!
      // You said he is from This race, but now you are saying it's not anymore?
      if (previous == now) {
        setAsLier(statement.author);
      }
    }

    if (subjectSupposedNotRaces[statement.author][statement.subject].size() > 1) {
      process_other_is_not_from_races(statement);
    }

    if (statement.author == statement.subject) {
      process_self_not_from_race(statement);
    }
    else if (subjects[statement.subject] != Inhabitant::Unknown) {
      if (subjects[statement.subject] == now) {
        setAsLier(statement.author);
      }
      else {
        setAsTrusted(statement.author);
      }
    }

    process_lier_and_trust_for_negative(statement);

    return false;
  }

  void considerOtherAsLier(const Statement& statement) {
    subjectSupposedLiers[statement.author][statement.subject] = true;
    auto trusted  = subjectSupposedTrusted[statement.author][statement.subject];
    if (trusted) {
      setAsLier(statement.author);
    }
  }

  void considerOtherAsTrusted(const Statement& statement) {
    auto untrusted = subjectSupposedLiers[statement.author][statement.subject];
    subjectSupposedTrusted[statement.author][statement.subject] = true;

    // contradiction
    if (untrusted) {
      setAsLier(statement.author);
    }
  }

  bool process_self_statement(const Statement& statement) {
    Inhabitant Iam = getInhabitant(statement.statement);
    // Impossible, evil beings only tell lies
    if (Iam == Inhabitant::Evil) {
      setPeriod(Period::Night);
      setAsHuman(statement.author);
    }
    else if (Iam == Inhabitant::Human) {
      setNotDivine(statement.author);
      setNotHumanNight(statement.author);
    }
    else if (Iam == Inhabitant::Devine) {
      setNotHumanDay(statement.author);
    }
    return false;
  }

  void process_supposition(const Statement& statement) {
    Inhabitant previous = subjectSupposedRaces[statement.author][statement.subject];
    Inhabitant now = getInhabitant(statement.statement);

    if (previous != Inhabitant::Unknown) {
      // Ha! you are contradicting yourself!
      if (previous != now) {
        if (!lier[statement.author]) {
          setAsLier(statement.author);
        }
      }
    }
    subjectSupposedRaces[statement.author][statement.subject] = now;
  }

  void process_subject_statement_based_on_Period(const Statement& statement) {
    Inhabitant heIs = getInhabitant(statement.statement);
    if (heIs == Inhabitant::Evil ||
      (period == Period::Night && heIs == Inhabitant::Human) ||
      (subjectSupposedDayOrNight[statement.author] == Period::Night && heIs == Inhabitant::Human)
      )
    {
      considerOtherAsLier(statement);
    }
    else if (heIs == Inhabitant::Devine ||
      (period == Period::Day && heIs == Inhabitant::Human) ||
      (subjectSupposedDayOrNight[statement.author] == Period::Day && heIs == Inhabitant::Human))
    {
      considerOtherAsTrusted(statement);
    }

    if (heIs == Inhabitant::Evil) {
      if (subjectSupposedDayOrNight[statement.author] == Period::Day &&
          heSaysHeIsHuman(statement.subject))
      {
        // subject is a lier, because if the author was lying, then it would night
        // and humans lies at night
        setPeriod(Period::Day);
        setAsTrusted(statement.author);
        setAsEvil(statement.subject);
      }
    }
  }

  void process_lier_and_trust(const Statement& statement) {
    Inhabitant heIs = getInhabitant(statement.statement);

    if (truthTeller[statement.author]) {
      if (Inhabitant::Devine == heIs) {
        setAsDevine(statement.subject);
      }
      else if (Inhabitant::Human == heIs) {
        setAsHuman(statement.subject);
      }
      else if (Inhabitant::Evil == heIs) {
        setAsEvil(statement.subject);
      }
    }
    else if (lier[statement.author]) {
      if (Inhabitant::Devine == heIs) {
        setNotDivine(statement.subject);
      }
      else if (Inhabitant::Human == heIs) {
        setNotHuman(statement.subject);
      }
      else if (Inhabitant::Evil == heIs) {
        setNotEvil(statement.subject);
      }
    }
  }

  bool process_subject_statement(const Statement& statement) {
    Inhabitant heIs = getInhabitant(statement.statement);

    process_supposition(statement);

    if (statement.author == statement.subject) {
      process_self_statement(statement);
    }
    else {
      process_subject_statement_based_on_Period(statement);
      if (subjects[statement.subject] != Inhabitant::Unknown) {
        if (subjects[statement.subject] == heIs) {
          setAsTrusted(statement.author);
        }
        else {
          setAsLier(statement.author);
        }
      }
    }

    process_lier_and_trust(statement);
    return false;
  }

  bool process(const Statement& statement) {
    if (statement.statement == "lying") {
      return process_lying_statement(statement);
    }

    if (statement.subject == "It") {
      return process_period_statement(statement);
    }

    return process_subject_statement(statement);
  }

  std::vector<Statement> getDeductions() {
    std::vector<Statement> deductions;

    for (const auto& hab : inhabitants) {
      checkPossibleRaces(hab);
    }

    for (const auto& entry : subjects) {
      if (entry.second != Inhabitant::Unknown) {
        deductions.push_back(Statement{ entry.first, "is", to_string(entry.second) });
      }
    }
    if (period != Period::Unknown) {
      deductions.push_back(Statement{ "It", "is", to_string(period) });
    }
    return deductions;
  }

  void simulateAsTrusted(const std::string& trustOnThis, const std::vector<Statement>& statements) {
    Solution simulated = *this;
    simulated.setAsTrusted(trustOnThis);
    while (simulated.process_statements(statements));
  }

  void simulateAsLier(const std::string& trustOnThis, const std::vector<Statement>& statements) {
    Solution simulated = *this;
    simulated.setAsLier(trustOnThis);
    while (simulated.process_statements(statements));
  }

  bool process_statements(const std::vector<Statement>& statements) {
    bool hadDeductions = false;
    for (const auto& statement : statements) {
      auto possibleToBe1 = this->subjectPossibleRaces[statement.author].size();
      auto possibleToBe2 = (statement.subject != "It") ? this->subjectPossibleRaces[statement.subject].size() : 0;
      auto periodBefore  = period;
      hadDeductions |=
          statement.isDeny ? process_negative(statement) : process(statement);
      hadDeductions |=
          possibleToBe1 != this->subjectPossibleRaces[statement.author].size() ||
          possibleToBe2 != ((statement.subject != "It") ? this->subjectPossibleRaces[statement.subject].size() : 0) ||
          periodBefore  != period;
    }
    return hadDeductions;
  }

  std::string solve(const std::vector<Statement>& statements) {
    for (const auto& statement : statements) {
      if (!inhabitants.count(statement.author)) {
        addInhabitant(statement.author);
      }

      if (statement.subject != "It" && !inhabitants.count(statement.subject)) {
        addInhabitant(statement.subject);
      }
    }

    try {
      bool hadDeductions = true;
      while (hadDeductions) {
        while (hadDeductions) {
          hadDeductions = process_statements(statements);
        }

        for (const auto& inhabitant : inhabitants) {
          bool rejectedAsLier{ false }, rejectedAsTrusted{ false };

          try {
            if (!lier[inhabitant] && !truthTeller[inhabitant]) {
              simulateAsTrusted(inhabitant, statements);
            }
          } catch (const AbsurdException& err) {
            rejectedAsTrusted = true;
          }

          try {
            if (!lier[inhabitant] && !truthTeller[inhabitant]) {
              simulateAsLier(inhabitant, statements);
            }
          } catch (const AbsurdException& err) {
            rejectedAsLier = true;
          }

          if (rejectedAsLier && rejectedAsTrusted) {
            throw AbsurdException{};
          }
          else if (rejectedAsLier) {
            setAsTrusted(inhabitant);
          }
          else if (rejectedAsTrusted) {
            setAsLier(inhabitant);
          }
          hadDeductions |= rejectedAsLier || rejectedAsTrusted;
        }
      }

      std::stringstream ss;
      std::vector<Statement> deductions = getDeductions();
      if (deductions.empty()) return Statement::notDeducible() + "\n";

      for (const auto& sol : deductions) {
        ss << sol.as_answer() << "\n";
      }
      return ss.str();

    }
    catch (std::exception& err) {
      return std::string(err.what()) + "\n";
    }
    return "";
  };
};


int main() {
  std::ios_base::sync_with_stdio(false);
  std::string line;
  std::int32_t numberOfstatements;
  std::int32_t conversation = 1;

  while (std::cin >> numberOfstatements && numberOfstatements) {
    Solution solution;
    std::vector<Statement> statements;

    for (auto ii = 0; ii < numberOfstatements; ii++) {
      statements.emplace_back(Statement{}.read(std::cin));
    }
    std::cout << "Conversation #" << conversation++ << "\n"
              << solution.solve(statements) + "\n";
  }

  return(0);
}