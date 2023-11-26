import opentuner
from opentuner import ConfigurationManipulator
from opentuner import IntegerParameter
from opentuner import MeasurementInterface
from opentuner import Result

class BasicScoreTuner(MeasurementInterface):

    def manipulator(self):
        manipulator = ConfigurationManipulator()
    
        manipulator.add_parameter(IntegerParameter('param1', 0, 3))
        manipulator.add_parameter(IntegerParameter('param2', 0, 3))
        manipulator.add_parameter(IntegerParameter('param3', 0, 3))
        manipulator.add_parameter(IntegerParameter('param4', 0, 3))
        manipulator.add_parameter(IntegerParameter('param5', 0, 3))
        manipulator.add_parameter(IntegerParameter('param6', 0, 3))
        manipulator.add_parameter(IntegerParameter('param7', 0, 3))
        manipulator.add_parameter(IntegerParameter('param8', 0, 3))
        manipulator.add_parameter(IntegerParameter('param9', 0, 3))

        return manipulator

    
    def run(self, desired_result, input, limit):
        cfg = desired_result.configuration.data
        cmd = f"./analysis.out {cfg['param1']} {cfg['param2']} {cfg['param3']} {cfg['param4']} {cfg['param5']} {cfg['param6']} {cfg['param7']} {cfg['param8']} {cfg['param9']}"

        result = self.call_program(cmd)
        if(result['returncode'] != 0):
            return Result(time=float('inf'), accuracy=0)
        
        performance = float(result['stdout'])
        if(performance == 0):
            return Result(time=float('inf'), accuracy=0)

        return Result(time=result['time'], accuracy=performance)
    
    def save_final_config(self, configuration):
        print("Melhor configuração escrita no arquivo: ", configuration.data)
        self.manipulator().save_to_file(configuration.data, 'final_config.json')
    

if __name__ == '__main__':
    argparser = opentuner.default_argparser()
    BasicScoreTuner.main(argparser.parse_args())