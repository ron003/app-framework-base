/**
 * @file CommandFacility interface
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have received with this code.
 */

#ifndef app_framework_core_Services_CommandFacility_hh
#define app_framework_core_Services_CommandFacility_hh

#include <list>
#include <memory>

namespace appframework {
class DAQProcess;  // forward declaration

/**
 * @brief Interface needed by Application Framework for CCM command handling
 */
class CommandFacility {
   public:
    /**
     * @brief Singleton pattern; get a handle to the CommandFacility
     * @return Static handle to the CommandFacility
     */
    static std::unique_ptr<CommandFacility> const& handle() {
        if (!handle_) handle_.reset(new CommandFacility());
        return handle_;
    }
    /**
     * @brief Perform basic setup actions needed by the CommandFacility, using command-line arguments and environment variables
     * @param args Command-line arguments to the CommandFacility
     */
    static void setup(std::list<std::string> /*args*/) {}
    /**
     * @brief Listen for commands and relay them to the given DAQProcess
     * @param process DAQProcess to relay commands to
     * @return Return code for application
     *
     * This function should block for the lifetime of the DAQ Application, calling DAQProcess::execute_command as necessary
     */
    virtual int listen(DAQProcess* /*process*/) { return 0; }

   protected:
    /**
     * Singleton pattern; protected parameterless constructor
     */
    CommandFacility() {}

   private:
    static std::unique_ptr<CommandFacility> handle_; ///< Singleton pattern, handle to CommandFacility
};
}  // namespace appframework

#endif  // app_framework_core_Services_CommandFacility_hh